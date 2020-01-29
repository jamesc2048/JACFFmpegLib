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


        JACFFMPEGLIB_EXPORT int streamIndex();
        JACFFMPEGLIB_EXPORT AVMediaType codecType();
        JACFFMPEGLIB_EXPORT uint32_t codecTag();
        JACFFMPEGLIB_EXPORT string codecTagString();
        JACFFMPEGLIB_EXPORT AVCodecID codecId();
        JACFFMPEGLIB_EXPORT int64_t duration();
        JACFFMPEGLIB_EXPORT double durationSeconds();
        JACFFMPEGLIB_EXPORT int64_t bitrate();
        JACFFMPEGLIB_EXPORT AVRational timeBase();
        JACFFMPEGLIB_EXPORT int64_t frameCount();

        // TODO side data

        // Video
        JACFFMPEGLIB_EXPORT int width();
        JACFFMPEGLIB_EXPORT int height();
        JACFFMPEGLIB_EXPORT AVPixelFormat pixelFormat();
        JACFFMPEGLIB_EXPORT AVRational sampleAspectRatio();
        JACFFMPEGLIB_EXPORT AVRational frameRate();
        JACFFMPEGLIB_EXPORT AVRational baseFrameRate();

        // Audio
        JACFFMPEGLIB_EXPORT AVSampleFormat sampleFormat();
        JACFFMPEGLIB_EXPORT int sampleRate();
        JACFFMPEGLIB_EXPORT int channels();
    };

//    class VideoStream : Stream
//    {
//    };

//    class AudioStream : Stream
//    {
//    };
}
