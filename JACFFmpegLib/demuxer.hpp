#pragma once

#include "common.hpp"

#include "stream.hpp"
#include "packet.hpp"

namespace JACFFmpegLib
{
    class Demuxer
    {
    private:
        AVFormatContext* formatCtx;

        string url;
        vector<Stream> streams;
        bool eosFlag = false;
        int bestVideoStreamIndex = -1;
        int bestAudioStreamIndex = -1;

    public:
        JACFFMPEGLIB_EXPORT Demuxer(string url);
        JACFFMPEGLIB_EXPORT ~Demuxer();

        JACFFMPEGLIB_EXPORT bool isEOS();
        JACFFMPEGLIB_EXPORT Packet nextPacket();
        JACFFMPEGLIB_EXPORT bool seekToKeyframe(double seconds);

        DISALLOW_COPY_AND_MOVE(Demuxer)
    };
}


