#ifndef MUXER_HPP
#define MUXER_HPP

#include "common.hpp"

#include "packet.hpp"
#include "stream.hpp"

namespace JACFFmpegLib
{
    class Muxer
    {
    private:
        AVFormatContext* formatCtx;
        vector<shared_ptr<Stream>> _streams;
        string _outputUri;

    public:
        JACFFMPEGLIB_EXPORT Muxer(string outputUri);
        JACFFMPEGLIB_EXPORT ~Muxer();

        //vector<Stream>& streams();
        //void addStream(Stream stream);
        JACFFMPEGLIB_EXPORT void copyStreams(const vector<shared_ptr<Stream>>& streams);
        JACFFMPEGLIB_EXPORT void writePacket(Packet &packet);
        JACFFMPEGLIB_EXPORT void close();
    };
}

#endif // MUXER_HPP
