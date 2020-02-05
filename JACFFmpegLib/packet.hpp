#ifndef PACKET_HPP
#define PACKET_HPP

#include "common.hpp"
#include "stream.hpp"

namespace JACFFmpegLib
{
    class Packet
    {
    private:
        AVPacketPtr _packet;
        AVMediaType _mediaType = AVMediaType::AVMEDIA_TYPE_UNKNOWN;
        AVCodecID _codecId = AVCodecID::AV_CODEC_ID_NONE;
        AVRational _timebase = {0, 0};
        weak_ptr<Stream> _streamRef;

    public:
        DISALLOW_COPY(Packet);

        JACFFMPEGLIB_EXPORT Packet();
        JACFFMPEGLIB_EXPORT Packet(AVPacket *_packet);
        JACFFMPEGLIB_EXPORT Packet(AVPacketPtr _packet);
        JACFFMPEGLIB_EXPORT ~Packet();
        JACFFMPEGLIB_EXPORT Packet(Packet &&) = default;
        JACFFMPEGLIB_EXPORT Packet& operator=(Packet &&) = default;

        // Custom properties
        JACFFMPEGLIB_EXPORT AVMediaType mediaType();
        JACFFMPEGLIB_EXPORT void setMediaType(AVMediaType _mediaType);
        JACFFMPEGLIB_EXPORT AVCodecID codecId();
        JACFFMPEGLIB_EXPORT void setCodecId(AVCodecID _codecId);
        JACFFMPEGLIB_EXPORT weak_ptr<Stream> streamRef();
        JACFFMPEGLIB_EXPORT AVRational streamTimebase();

        // AVPacket getters/setters
        JACFFMPEGLIB_EXPORT bool hasData();
        JACFFMPEGLIB_EXPORT int streamIndex();

        // Methods
        JACFFMPEGLIB_EXPORT Packet clone();

        // Internal methods
        AVPacketPtr& avpacket();
        void setStreamRef(weak_ptr<Stream> stream);
        void setStreamTimebase(AVRational timebase);
    };
}

#endif // PACKET_HPP
