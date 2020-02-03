#pragma once

#include "common.hpp"

#define CHECK_MEDIA_TYPE(mediaType) \
    if (codecType() != mediaType) \
    { \
        THROW_EXCEPTION("Cannot access Video property on stream type %s"); \
    }

namespace JACFFmpegLib
{
    class Stream
    {
    protected:
        AVStream *stream = nullptr;

    public:
        JACFFMPEGLIB_EXPORT Stream(AVStream *stream);
        JACFFMPEGLIB_EXPORT ~Stream();
        JACFFMPEGLIB_EXPORT Stream(const Stream &) = default;
        JACFFMPEGLIB_EXPORT Stream& operator=(const Stream &) = default;
        JACFFMPEGLIB_EXPORT Stream(Stream &&) = default;
        JACFFMPEGLIB_EXPORT Stream& operator=(Stream &&) = default;


        JACFFMPEGLIB_EXPORT int streamIndex() const;
        JACFFMPEGLIB_EXPORT AVMediaType codecType() const;
        JACFFMPEGLIB_EXPORT uint32_t codecTag() const;
        JACFFMPEGLIB_EXPORT string codecTagString() const;
        JACFFMPEGLIB_EXPORT AVCodecID codecId() const;
        JACFFMPEGLIB_EXPORT int64_t duration() const;
        JACFFMPEGLIB_EXPORT double durationSeconds() const;
        JACFFMPEGLIB_EXPORT int64_t bitrate() const;
        JACFFMPEGLIB_EXPORT AVRational timeBase() const;
        JACFFMPEGLIB_EXPORT int64_t frameCount() const;

        // TODO side data

        // Video
        JACFFMPEGLIB_EXPORT int width() const;
        JACFFMPEGLIB_EXPORT int height() const;
        JACFFMPEGLIB_EXPORT AVPixelFormat pixelFormat() const;
        JACFFMPEGLIB_EXPORT AVRational sampleAspectRatio() const;
        JACFFMPEGLIB_EXPORT AVRational frameRate() const;
        JACFFMPEGLIB_EXPORT AVRational baseFrameRate() const;

        // Audio
        JACFFMPEGLIB_EXPORT AVSampleFormat sampleFormat() const;
        JACFFMPEGLIB_EXPORT int sampleRate() const;
        JACFFMPEGLIB_EXPORT int channels() const;

        // Internal
        AVCodecParameters* codecParams() const;
    };

//    class VideoStream : Stream
//    {
//    };

//    class AudioStream : Stream
//    {
//    };
}
