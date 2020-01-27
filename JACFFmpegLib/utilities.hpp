#ifndef UTILITIES_H
#define UTILITIES_H

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

    AVPacketPtr make_avpacket(AVPacket *packet);
}

#endif // UTILITIES_H
