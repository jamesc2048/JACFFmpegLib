#pragma once

#include "common.hpp"

#include "stream.hpp"
#include "packet.hpp"

namespace JACFFmpegLib
{
    class Demuxer
    {
    private:
        AVFormatContext* formatCtx = nullptr;

        string url;
        vector<shared_ptr<Stream>> streams;
        bool eosFlag = false;
        int bestVideoStreamIndex = AVERROR_STREAM_NOT_FOUND;
        int bestAudioStreamIndex = AVERROR_STREAM_NOT_FOUND;

    public:
        JACFFMPEGLIB_EXPORT Demuxer(string url);
        JACFFMPEGLIB_EXPORT ~Demuxer();

        JACFFMPEGLIB_EXPORT const vector<shared_ptr<Stream>>& getStreams();
        JACFFMPEGLIB_EXPORT bool hasVideo();
        JACFFMPEGLIB_EXPORT bool hasAudio();
        JACFFMPEGLIB_EXPORT weak_ptr<Stream> getBestVideoStream();
        JACFFMPEGLIB_EXPORT weak_ptr<Stream> getBestAudioStream();
        JACFFMPEGLIB_EXPORT bool isEOS();
        JACFFMPEGLIB_EXPORT Packet nextPacket();
        JACFFMPEGLIB_EXPORT bool seekToKeyframe(double seconds);

        DISALLOW_COPY_AND_MOVE(Demuxer)
    };
}


