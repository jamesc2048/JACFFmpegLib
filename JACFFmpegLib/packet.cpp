#include "packet.hpp"

namespace JACFFmpegLib
{
    Packet::Packet(AVPacket *packet)
        : Packet(make_avpacket(packet))
    {
    }

    Packet::Packet(AVPacketPtr packet)
                    : _packet(move(packet))
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
        _packet = make_avpacket(av_packet_alloc());

        _packet->size = 0;
        _packet->data = nullptr;
        _packet->buf = nullptr;
    }

    AVPacketPtr& Packet::avpacket()
    {
        return _packet;
    }

    void Packet::setStreamRef(weak_ptr<Stream> stream)
    {
        _streamRef = stream;
    }

    void Packet::setStreamTimebase(AVRational timebase)
    {
        _timebase = timebase;
    }

    bool Packet::hasData()
    {
        assert(_packet);

        // Note that packet will always be non-null (unless somebody sets it to null...)
        return _packet->size > 0 && _packet->data;
    }

    void Packet::setMediaType(AVMediaType codecType)
    {
        this->_mediaType = codecType;
    }

    AVCodecID Packet::codecId()
    {
        return _codecId;
    }

    void Packet::setCodecId(AVCodecID codecId)
    {
        this->_codecId = codecId;
    }

    std::weak_ptr<Stream> Packet::streamRef()
    {
        // Reference to the stream in the Demuxer object that
        // If you deallocate the Demuxer object, the Stream objects will go out of scope and as such
        // you may not use the stream reference any more.
        return _streamRef;
    }

    AVRational Packet::streamTimebase()
    {
        return _timebase;
    }

    AVMediaType Packet::mediaType()
    {
        return _mediaType;
    }

    int Packet::streamIndex()
    {
        // TODO can this be -1?
        return _packet->stream_index;
    }

    Packet Packet::clone()
    {
        if (_packet->side_data_elems > 0)
        {
            THROW_EXCEPTION("Side data copying not implemented!");
        }

        Packet clonePacket;

        AVPacket* cloneAVPacket = clonePacket.avpacket().get();
        const AVPacket* oldAVPacket = avpacket().get();

        cloneAVPacket->size = cloneAVPacket->size;
        // https://stackoverflow.com/questions/12929330/create-a-copy-of-an-avpacket-structure
        // Surely there's better way to get the alignment right?
        cloneAVPacket->data = reinterpret_cast<uint8_t *>(new uint64_t[(oldAVPacket->size + AV_INPUT_BUFFER_PADDING_SIZE) / sizeof(uint64_t) + 1]);
        memcpy(cloneAVPacket->data, oldAVPacket->data, oldAVPacket->size);

        av_packet_copy_props(cloneAVPacket, oldAVPacket);

        clonePacket.setMediaType(mediaType());
        clonePacket.setStreamRef(streamRef());

        return clonePacket;
    }
}
