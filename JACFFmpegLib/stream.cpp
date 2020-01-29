#include "stream.hpp"

namespace JACFFmpegLib
{
    Stream::Stream(AVStream *stream)
                    : stream(stream)
    {
        if (!stream)
        {
            THROW_EXCEPTION("Null stream passed to constructor");
        }
    }

    int Stream::streamIndex()
    {
        return stream->index;
    }

    Stream::~Stream()
    {
        // Do not delete stream ptr: it is owned by a AVFormatContext
    }

    // General AVStream properties
    AVMediaType Stream::codecType()
    {
        return stream->codecpar->codec_type;
    }

    uint32_t Stream::codecTag()
    {
        return stream->codecpar->codec_tag;
    }

    std::string Stream::codecTagString()
    {
        uint32_t c = stream->codecpar->codec_tag;

        char chars[4] = { static_cast<char>((c >> 24) & 0xFF),
                          static_cast<char>((c >> 16) & 0xFF),
                          static_cast<char>((c >> 8) & 0xFF),
                          static_cast<char>((c >> 0) & 0xFF) };

        return { chars };
    }



    AVCodecID Stream::codecId()
    {
        return stream->codecpar->codec_id;
    }

    int64_t Stream::duration()
    {
        return stream->duration;
    }

    double Stream::durationSeconds()
    {
        return Utils::timestampToSeconds(stream->duration, stream->time_base);
    }

    int64_t Stream::bitrate()
    {
        return stream->codecpar->bit_rate;
    }

    AVRational Stream::timeBase()
    {
        return stream->time_base;
    }

    int64_t Stream::frameCount()
    {
        return stream->nb_frames;
    }

    // Video-only properties
    int Stream::width()
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return stream->codecpar->width;
    }

    int Stream::height()
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return stream->codecpar->height;
    }

    AVPixelFormat Stream::pixelFormat()
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return static_cast<AVPixelFormat>(stream->codecpar->format);
    }

    AVRational Stream::sampleAspectRatio()
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return stream->codecpar->sample_aspect_ratio;
    }

    AVRational Stream::frameRate()
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return stream->avg_frame_rate;
    }

    AVRational Stream::baseFrameRate()
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return stream->r_frame_rate;
    }

    // Audio-only properties
    AVSampleFormat Stream::sampleFormat()
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_AUDIO);

        return static_cast<AVSampleFormat>(stream->codecpar->format);
    }

    int Stream::sampleRate()
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_AUDIO);

        return stream->codecpar->sample_rate;
    }

    int Stream::channels()
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_AUDIO);

        return stream->codecpar->channels;
    }
}
