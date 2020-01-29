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
        if (!packet)
        {
            THROW_EXCEPTION("Null packet passed");
        }
    }

    Packet::~Packet()
    {
        // Nothing to do
    }

    Packet::Packet()
    {
        packet = make_avpacket(av_packet_alloc());

        packet->size = 0;
        packet->data = nullptr;
        packet->buf = nullptr;
    }

    AVPacketPtr& Packet::getAVPacket()
    {
        // Needed for internal operations. Hidden to external API.
        return packet;
    }

    void Packet::setStreamRef(weak_ptr<Stream> stream)
    {
        streamRef = stream;
    }

    bool Packet::hasData()
    {
        // Note that packet will always be non-null (unless somebody sets it to null...)
        return packet->size > 0 && packet->data;
    }

    void Packet::setCodecType(AVMediaType codecType)
    {
        this->codecType = codecType;
    }

    std::weak_ptr<Stream> Packet::getStreamRef()
    {
        // Reference to the stream in the Demuxer object that
        // If you deallocate the Demuxer object, the Stream objects will go out of scope and as such
        // you may not use the stream reference any more.
        return streamRef;
    }

    AVMediaType Packet::getCodecType()
    {
        return codecType;
    }

    size_t Packet::getStreamIndex()
    {
        return packet->stream_index;
    }

    Packet Packet::clone()
    {
        if (packet->side_data_elems > 0)
        {
            THROW_EXCEPTION("Side data copying not implemented!");
        }

        Packet clonePacket;

        AVPacket* cloneAVPacket = clonePacket.getAVPacket().get();
        const AVPacket* oldAVPacket = packet.get();

        cloneAVPacket->size = cloneAVPacket->size;
        // https://stackoverflow.com/questions/12929330/create-a-copy-of-an-avpacket-structure
        // Surely there's better way to get the alignment right?
        cloneAVPacket->data = reinterpret_cast<uint8_t *>(new uint64_t[(oldAVPacket->size + AV_INPUT_BUFFER_PADDING_SIZE) / sizeof(uint64_t) + 1]);
        memcpy(cloneAVPacket->data, oldAVPacket->data, oldAVPacket->size);

        av_packet_copy_props(cloneAVPacket, oldAVPacket);

        clonePacket.setCodecType(getCodecType());
        clonePacket.setStreamRef(getStreamRef());

        // TODO
//        // TODO avoid deprecated func
//        av_copy_packet(clonePacket.getAVPacket().get(), packet.get());

        return clonePacket;
    }
}
