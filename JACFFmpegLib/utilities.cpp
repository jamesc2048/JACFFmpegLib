#include "utilities.hpp"

namespace JACFFmpegLib
{
    namespace Utils
    {
        std::string avErrorToStr(int errnum)
        {
            char *buf = new char[AV_ERROR_MAX_STRING_SIZE];
            return av_make_error_string(buf, AV_ERROR_MAX_STRING_SIZE, errnum);
        }

        void log(const std::string &message)
        {
            av_log(nullptr, AV_LOG_INFO, "%s", message.c_str());
        }

        int64_t secondsToTimestamp(double secs, AVRational timebase)
        {
            // TODO better way of doing this?
            return static_cast<int64_t>((secs * timebase.num) / static_cast<double>(timebase.den));
        }

        double timestampToSeconds(int64_t timestamp, AVRational timebase)
        {
            return timestamp * av_q2d(timebase);
        }
    }

    void AVPacketDeleter::operator()(AVPacket *packet)
    {
        if (packet)
        {
            av_packet_free(&packet);
        }
    }

    AVPacketPtr make_avpacket(AVPacket *packet)
    {
        return AVPacketPtr(packet);
    }

    void AVFrameDeleter::operator()(AVFrame *frame)
    {
        if (frame)
        {
            av_frame_free(&frame);
        }
    }
}
