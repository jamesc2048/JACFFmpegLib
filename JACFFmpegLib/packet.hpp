#ifndef PACKET_HPP
#define PACKET_HPP

#include "pch.hpp"

namespace JACFFmpegLib
{
    class Packet
    {
    private:
        AVPacketPtr packet;

    public:
        JACFFMPEGLIB_EXPORT Packet();
        JACFFMPEGLIB_EXPORT Packet(AVPacket *packet);
        JACFFMPEGLIB_EXPORT Packet(AVPacketPtr packet);

        JACFFMPEGLIB_EXPORT AVPacketPtr& getAVPacket();

        DISALLOW_COPY(Packet)
        Packet(Packet &&) = default;
        Packet& operator=(Packet &&) = default;

    };
}

#endif // PACKET_HPP
