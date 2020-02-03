#ifndef UTILITIES_H
#define UTILITIES_H

#include "pch.hpp"

using std::string;
using std::unique_ptr;

namespace JACFFmpegLib
{
    namespace Utils
    {
        string avErrorToStr(int errnum);
        void log(const string &message);
        int64_t secondsToTimestamp(double secs, AVRational timebase);
        double timestampToSeconds(int64_t timestamp, AVRational timebase);
    }

    struct AVPacketDeleter
    {
        void operator()(AVPacket *packet);
    };

    using AVPacketPtr = unique_ptr<AVPacket, AVPacketDeleter>;

    struct AVFrameDeleter
    {
        void operator()(AVFrame *frame);
    };

    using AVFramePtr = unique_ptr<AVFrame, AVFrameDeleter>;

    AVPacketPtr make_avpacket(AVPacket *packet);
    AVFramePtr make_avframe(AVFrame *frame);
}

#endif // UTILITIES_H
