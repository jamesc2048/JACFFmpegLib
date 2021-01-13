#ifndef VIDEODECODER_HPP
#define VIDEODECODER_HPP

#include "common.hpp"
#include "stream.hpp"
#include "packet.hpp"
#include "frame.hpp"

namespace JACFFmpegLib
{
    class VideoDecoder
    {
    private:
        AVCodecContext *codecCtx = nullptr;
        AVRational lastPacketTimebase = {0, 0};

    public:
        JACFFMPEGLIB_EXPORT VideoDecoder(const Stream& stream);
        JACFFMPEGLIB_EXPORT ~VideoDecoder();

        JACFFMPEGLIB_EXPORT FrameList decodePacket(Packet& p);
        JACFFMPEGLIB_EXPORT FrameList drain();
        JACFFMPEGLIB_EXPORT void flushBuffers();

        DISALLOW_COPY_AND_MOVE(VideoDecoder)
    };
}

#endif // VIDEODECODER_HPP
