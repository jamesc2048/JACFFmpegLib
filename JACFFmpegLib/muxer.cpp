#include "muxer.hpp"

namespace JACFFmpegLib
{
    Muxer::Muxer(string outputUri) : _outputUri(outputUri)
    {
        int ret = avformat_alloc_output_context2(&formatCtx, nullptr, nullptr, outputUri.c_str());

        if (ret < 0)
        {
            THROW_EXCEPTION("Failed to create output context");
        }

        if (!(formatCtx->flags & AVFMT_NOFILE)) {
             ret = avio_open(&formatCtx->pb, outputUri.c_str(), AVIO_FLAG_WRITE);

             if (ret < 0)
             {
                 THROW_EXCEPTION("open file");
             }
         }
    }

    Muxer::~Muxer()
    {
        close();
    }

//    void Muxer::addStream(Stream stream)
//    {
//        AVStream *stream = avformat_new_stream(formatCtx, nullptr);

//        av_dump_format(formatCtx, 0, _outputUri.c_str(), 1);
//    }

    void Muxer::copyStreams(const vector<shared_ptr<Stream>>& streams)
    {
        for (const auto& stream : streams)
        {
            AVStream *newStream = avformat_new_stream(formatCtx, nullptr);
            newStream->time_base = stream->timebase();

            if (!newStream)
            {
                THROW_EXCEPTION("newStream");
            }

            int ret = avcodec_parameters_copy(newStream->codecpar, stream->codecParams());

            if (ret != 0)
            {
                THROW_EXCEPTION("params copy");
            }

            _streams.emplace_back(make_shared<Stream>(newStream));

            av_dump_format(formatCtx, (int)(streams.size() - 1), _outputUri.c_str(), 1);
        }

        int ret = avformat_write_header(formatCtx, nullptr);

        if (ret < 0)
        {
            if (ret < 0)
            {
                THROW_EXCEPTION("write header");
            }
        }
    }

    void Muxer::writePacket(Packet &packet)
    {
        if (packet.hasData())
        {
            auto p = packet.avpacket().get();
            int ret = av_interleaved_write_frame(formatCtx, p);

            if (ret < 0)
            {
                THROW_EXCEPTION("write_frame");
            }
        }
    }

    void Muxer::close()
    {
        if (formatCtx)
        {
            int ret;

            // if this fails, throw exception after finishing cleanup
            ret = av_write_trailer(formatCtx);

            if (!(formatCtx->flags & AVFMT_NOFILE))
            {
                /* Close the output file. */
                avio_closep(&formatCtx->pb);
            }

            // TODO this also works for outputs?
            if (formatCtx)
            {
                avformat_close_input(&formatCtx);
            }

            if (ret < 0)
            {
                //THROW_EXCEPTION("Writing trailer failed");
            }
        }
    }
}
