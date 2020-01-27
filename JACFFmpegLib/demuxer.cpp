#include "demuxer.hpp"

namespace JACFFmpegLib
{
    Demuxer::Demuxer(string url)
        : url(url)
    {
        int ret = avformat_open_input(&formatCtx, url.c_str(), nullptr, nullptr);

        if (ret < 0)
        {
            string error = Utils::avErrorToStr(ret);
            THROW_EXCEPTION("Failed to open url %s");
        }

        ret = avformat_find_stream_info(formatCtx, nullptr);

        if (ret < 0)
        {
            string error = Utils::avErrorToStr(ret);
            THROW_EXCEPTION("Failed to find stream info for url %s");
        }

        if (formatCtx->nb_streams == 0)
        {
            THROW_EXCEPTION("No streams in url %s");
        }

        av_dump_format(formatCtx, 0, url.c_str(), 0);

        bestVideoStreamIndex = av_find_best_stream(formatCtx, AVMediaType::AVMEDIA_TYPE_VIDEO, -1, 0, nullptr, 0);
        bestAudioStreamIndex = av_find_best_stream(formatCtx, AVMediaType::AVMEDIA_TYPE_AUDIO, -1, 0, nullptr, 0);

        if (bestVideoStreamIndex != AVERROR_STREAM_NOT_FOUND)
        {
            // We have video
        }

        if (bestAudioStreamIndex != AVERROR_STREAM_NOT_FOUND)
        {
            // We have audio
        }

        // TODO subtitles

        for (size_t i = 0; i < formatCtx->nb_streams; i++)
        {
            streams.emplace_back(formatCtx->streams[i]);
        }
    }

    Demuxer::~Demuxer()
    {
        if (formatCtx)
        {
            avformat_close_input(&formatCtx);
        }
    }

    bool Demuxer::isEOS()
    {
        return eosFlag;
    }

    Packet Demuxer::nextPacket()
    {
        Packet packet;

        int ret = av_read_frame(formatCtx, packet.getAVPacket().get());

        if (ret == AVERROR_EOF)
        {
            eosFlag = true;
            return {};
        }
        else if (ret < 0)
        {
            string error = Utils::avErrorToStr(ret);
            LOG(error);
        }

        return packet;
    }

    bool Demuxer::seekToKeyframe(double seconds)
    {
        // using stream 0 for this
        size_t streamIndex = 0;

        AVRational tb = streams[streamIndex].timeBase();

        int64_t streamTimestamp = Utils::secondsToTimestamp(seconds, tb);

        int flags = 0;

        int ret = avformat_seek_file(formatCtx, static_cast<int>(streamIndex), 0, streamTimestamp, streamTimestamp, flags);

        if (ret < 0)
        {
            string error = Utils::avErrorToStr(ret);
            LOG(error);
        }

        return ret >= 0;
    }
}
