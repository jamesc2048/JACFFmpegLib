#ifndef FRAME_HPP
#define FRAME_HPP

#include "common.hpp"

namespace JACFFmpegLib
{
    class Frame
    {
    private:
        AVFramePtr _frame;
        AVMediaType _mediaType = AVMediaType::AVMEDIA_TYPE_UNKNOWN;
        AVRational _timebase = {0, 0};

    public:
        DISALLOW_COPY(Frame);

        JACFFMPEGLIB_EXPORT Frame();
        JACFFMPEGLIB_EXPORT Frame(AVFrame *frame);
        JACFFMPEGLIB_EXPORT Frame(AVFramePtr frame);
        JACFFMPEGLIB_EXPORT ~Frame();
        JACFFMPEGLIB_EXPORT Frame(Frame &&) = default;
        JACFFMPEGLIB_EXPORT Frame& operator=(Frame &&) = default;

        // Custom properties
        JACFFMPEGLIB_EXPORT void setMediaType(AVMediaType mediaType);
        JACFFMPEGLIB_EXPORT AVMediaType mediaType();
        JACFFMPEGLIB_EXPORT void setTimebase(AVRational timebase);
        JACFFMPEGLIB_EXPORT AVRational timebase();

        // General AVFrame getters/setters
        JACFFMPEGLIB_EXPORT int64_t timestamp();
        JACFFMPEGLIB_EXPORT double timestampSeconds();

        // Video AVFrame getters/setters
        JACFFMPEGLIB_EXPORT size_t width();
        JACFFMPEGLIB_EXPORT size_t height();
        JACFFMPEGLIB_EXPORT AVPixelFormat pixelFormat();
        JACFFMPEGLIB_EXPORT AVRational sampleAspectRatio();

        // Audio AVFame getters/setters
        JACFFMPEGLIB_EXPORT AVSampleFormat sampleFormat();

        // Methods
        JACFFMPEGLIB_EXPORT vector<uint8_t> dumpToBytes();
        // Beware using AVFrame directly as it could break things. Giving access for flexibility's sake.
        JACFFMPEGLIB_EXPORT AVFramePtr& avframe();
    };

    using FrameList = std::vector<Frame>;
}

#endif // FRAME_HPP
