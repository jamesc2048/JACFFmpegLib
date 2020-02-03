#include "videodecoder.hpp"

namespace JACFFmpegLib
{
    VideoDecoder::VideoDecoder(const Stream &stream)
    {
        AVCodec *codec = avcodec_find_decoder(stream.codecId());

        if (!codec)
        {
            THROW_EXCEPTION("No codec found");
        }

        codecCtx = avcodec_alloc_context3(codec);

        if (!codecCtx)
        {
            THROW_EXCEPTION("Couldn't alloc codecCtx");
        }

        // Enable multithreading for decoder
        codecCtx->thread_count = (int)thread::hardware_concurrency();
        codecCtx->thread_type = FF_THREAD_FRAME;

        int ret = avcodec_parameters_to_context(codecCtx, stream.codecParams());

        if (ret < 0)
        {
            THROW_EXCEPTION("Couldn't convert parameters to context");
        }

        // TODO options
        AVDictionary* options = nullptr;

        ret = avcodec_open2(codecCtx, codec, &options);

        if (ret < 0)
        {
            THROW_EXCEPTION("Couldn't open codec!");
        }
    }

    VideoDecoder::~VideoDecoder()
    {
        if (codecCtx)
        {
            avcodec_free_context(&codecCtx);
        }
    }

    FrameList VideoDecoder::decodePacket(Packet& p)
    {
        AVPacketPtr& packet = p.getAVPacket();

        int ret = avcodec_send_packet(codecCtx, packet.get());

        if (ret < 0)
        {
            // TODO Handle all AVERROR() states
            if (ret == AVERROR_EOF)
            {
                return {};
            }
            else
            {
                THROW_EXCEPTION("Error sending packet");
            }
        }

        FrameList frameList;

        // Codec may return multiple frames per packet.
        while (true)
        {
            Frame frame;

            ret = avcodec_receive_frame(codecCtx, frame.getAVFrame().get());

            if (ret == 0)
            {
                // Got frame
                frameList.emplace_back(move(frame));
            }
            else
            {
                if (ret == AVERROR(EAGAIN))
                {
                    // No more data to be decoded, return list
                    return frameList;
                }
                else if (ret == AVERROR_EOF)
                {
                    // Decoder has been flushed
                    return {};
                }
                else
                {
                    THROW_EXCEPTION("Error whilst decoding");
                }
            }
        }
    }
}
