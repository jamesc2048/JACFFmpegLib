#ifndef PACKET_HPP
#define PACKET_HPP

#include "common.hpp"
#include "stream.hpp"

namespace JACFFmpegLib
{
    class Packet
    {
    private:
        AVPacketPtr packet;
        AVMediaType codecType = AVMediaType::AVMEDIA_TYPE_UNKNOWN;
        weak_ptr<Stream> streamRef;

    public:
        DISALLOW_COPY(Packet);

        JACFFMPEGLIB_EXPORT Packet();
        JACFFMPEGLIB_EXPORT Packet(AVPacket *packet);
        JACFFMPEGLIB_EXPORT Packet(AVPacketPtr packet);
        JACFFMPEGLIB_EXPORT ~Packet();
        JACFFMPEGLIB_EXPORT Packet(Packet &&) = default;
        JACFFMPEGLIB_EXPORT Packet& operator=(Packet &&) = default;

        JACFFMPEGLIB_EXPORT bool hasData();
        JACFFMPEGLIB_EXPORT size_t getStreamIndex();
        JACFFMPEGLIB_EXPORT AVMediaType getCodecType();
        JACFFMPEGLIB_EXPORT void setCodecType(AVMediaType codecType);
        JACFFMPEGLIB_EXPORT weak_ptr<Stream> getStreamRef();

        JACFFMPEGLIB_EXPORT Packet clone();

        // Internal methods
        AVPacketPtr& getAVPacket();
        void setStreamRef(weak_ptr<Stream> stream);
    };
}

#endif // PACKET_HPP
