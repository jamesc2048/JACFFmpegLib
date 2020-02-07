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

        string _url;
        vector<shared_ptr<Stream>> _streams;
        bool _eosFlag = false;
        int _bestVideoStreamIndex = AVERROR_STREAM_NOT_FOUND;
        int _bestAudioStreamIndex = AVERROR_STREAM_NOT_FOUND;

    public:
        JACFFMPEGLIB_EXPORT Demuxer(string _url);
        JACFFMPEGLIB_EXPORT ~Demuxer();

        // Getters
        JACFFMPEGLIB_EXPORT const vector<shared_ptr<Stream>>& streams();
        JACFFMPEGLIB_EXPORT bool hasVideo();
        JACFFMPEGLIB_EXPORT bool hasAudio();
        JACFFMPEGLIB_EXPORT weak_ptr<Stream> bestVideoStream();
        JACFFMPEGLIB_EXPORT weak_ptr<Stream> bestAudioStream();
        JACFFMPEGLIB_EXPORT bool isEOS();

        // Methods
        JACFFMPEGLIB_EXPORT Packet nextPacket();
        JACFFMPEGLIB_EXPORT bool seekToKeyframe(double seconds);

        DISALLOW_COPY_AND_MOVE(Demuxer)
    };
}


