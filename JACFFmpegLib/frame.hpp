#ifndef FRAME_HPP
#define FRAME_HPP

#include "common.hpp"

namespace JACFFmpegLib
{
    class Frame
    {
    private:
        AVFramePtr frame;

    public:
        DISALLOW_COPY(Frame);

        JACFFMPEGLIB_EXPORT Frame();
        JACFFMPEGLIB_EXPORT Frame(AVFrame *frame);
        JACFFMPEGLIB_EXPORT Frame(AVFramePtr frame);
        JACFFMPEGLIB_EXPORT ~Frame();
        JACFFMPEGLIB_EXPORT Frame(Frame &&) = default;
        JACFFMPEGLIB_EXPORT Frame& operator=(Frame &&) = default;

        JACFFMPEGLIB_EXPORT vector<uint8_t> dumpToBytes();

        // Internal methods
        AVFramePtr &getAVFrame();
    };

    using FrameList = std::vector<Frame>;
}

#endif // FRAME_HPP
