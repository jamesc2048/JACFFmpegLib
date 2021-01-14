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
        int ret;

        if (p.hasData())
        {
            lastPacketTimebase = p.streamTimebase();

            AVPacketPtr& packet = p.avpacket();

            ret = avcodec_send_packet(codecCtx, packet.get());
        }
        else
        {
            // Enter draining mode
            ret = avcodec_send_packet(codecCtx, nullptr);
        }

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

            ret = avcodec_receive_frame(codecCtx, frame.avframe().get());

            if (ret == 0)
            {
                // Got frame
                frameList.emplace_back(move(frame));

                Frame& lastFrame = frameList.back();

                lastFrame.setMediaType(AVMediaType::AVMEDIA_TYPE_VIDEO);
                lastFrame.setTimebase(codecCtx->time_base);

                lastFrame.avframe()->pts = av_rescale_q(lastFrame.avframe()->pts, lastPacketTimebase, codecCtx->time_base);
            }
            else
            {
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                {
                    // No more data to be decoded or decoder has been flushed, return list
                    return frameList;
                }
                else
                {
                    THROW_EXCEPTION("Error whilst decoding");
                }
            }
        }
    }

    FrameList VideoDecoder::drain()
    {
        Packet p;

        return decodePacket(p);
    }

    void VideoDecoder::flushBuffers()
    {
        // To be used when seeking
        avcodec_flush_buffers(codecCtx);
    }
}