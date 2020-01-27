#ifndef PACKET_HPP
#define PACKET_HPP

#include "pch.hpp"

namespace JACFFmpegLib
{
    class Packet
    {
    private:
        AVPacketPtr packet;
        AVMediaType codecType = AVMediaType::AVMEDIA_TYPE_UNKNOWN;

    public:
        JACFFMPEGLIB_EXPORT Packet();
        JACFFMPEGLIB_EXPORT Packet(AVPacket *packet);
        JACFFMPEGLIB_EXPORT Packet(AVPacketPtr packet);

        JACFFMPEGLIB_EXPORT AVPacketPtr& getAVPacket();
        JACFFMPEGLIB_EXPORT void setCodecType(AVMediaType codecType);
        JACFFMPEGLIB_EXPORT AVMediaType getCodecType();
        JACFFMPEGLIB_EXPORT size_t getStreamIndex();

        DISALLOW_COPY(Packet)
        Packet(Packet &&) = default;
        Packet& operator=(Packet &&) = default;

    };
}

#endif // PACKET_HPP
