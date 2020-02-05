#include "stream.hpp"

namespace JACFFmpegLib
{
    Stream::Stream(AVStream *stream)
                    : _stream(stream)
    {
        if (!stream)
        {
            THROW_EXCEPTION("Null stream passed to constructor");
        }
    }

    Stream::~Stream()
    {
        // Do not delete stream ptr: it is owned by a AVFormatContext
    }

    // General AVStream properties
    int Stream::streamIndex() const
    {
        return _stream->index;
    }

    AVMediaType Stream::mediaType() const
    {
        return _stream->codecpar->codec_type;
    }

    uint32_t Stream::codecTag() const
    {
        return _stream->codecpar->codec_tag;
    }

    std::string Stream::codecTagString() const
    {
        uint32_t c = _stream->codecpar->codec_tag;

        char chars[4] = { static_cast<char>((c >> 0) & 0xFF),
                          static_cast<char>((c >> 8) & 0xFF),
                          static_cast<char>((c >> 16) & 0xFF),
                          static_cast<char>((c >> 24) & 0xFF) };

        return { chars };
    }

    AVCodecID Stream::codecId() const
    {
        return _stream->codecpar->codec_id;
    }

    int64_t Stream::duration() const
    {
        return _stream->duration;
    }

    double Stream::durationSeconds() const
    {
        return Utils::timestampToSeconds(_stream->duration, _stream->time_base);
    }

    int64_t Stream::bitrate() const
    {
        return _stream->codecpar->bit_rate;
    }

    AVRational Stream::timebase() const
    {
        return _stream->time_base;
    }

    int64_t Stream::frameCount() const
    {
        return _stream->nb_frames;
    }

    // Video-only properties
    int Stream::width() const
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return _stream->codecpar->width;
    }

    int Stream::height() const
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return _stream->codecpar->height;
    }

    AVPixelFormat Stream::pixelFormat() const
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return static_cast<AVPixelFormat>(_stream->codecpar->format);
    }

    AVRational Stream::sampleAspectRatio() const
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return _stream->codecpar->sample_aspect_ratio;
    }

    AVRational Stream::frameRate() const
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return _stream->avg_frame_rate;
    }

    AVRational Stream::baseFrameRate() const
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return _stream->r_frame_rate;
    }

    // Audio-only properties
    AVSampleFormat Stream::sampleFormat() const
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_AUDIO);

        return static_cast<AVSampleFormat>(_stream->codecpar->format);
    }

    int Stream::sampleRate() const
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_AUDIO);

        return _stream->codecpar->sample_rate;
    }

    int Stream::channels() const
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_AUDIO);

        return _stream->codecpar->channels;
    }

    AVCodecParameters* Stream::codecParams() const
    {
        return _stream->codecpar;
    }
}
