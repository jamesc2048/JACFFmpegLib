#include "packet.hpp"

namespace JACFFmpegLib
{
    Packet::Packet(AVPacket *packet)
        : Packet(make_avpacket(packet))
    {
    }

    Packet::Packet(AVPacketPtr packet)
                    : packet(move(packet))
    {

    }

    AVPacketPtr& Packet::getAVPacket()
    {
        return packet;
    }

    void Packet::setCodecType(AVMediaType codecType)
    {
        this->codecType = codecType;
    }

    AVMediaType Packet::getCodecType()
    {
        return codecType;
    }

    size_t Packet::getStreamIndex()
    {
        return packet->stream_index;
    }

    Packet::Packet()
    {
        packet = make_avpacket(av_packet_alloc());

        packet->size = 0;
        packet->data = nullptr;
        packet->buf = nullptr;
    }
}
