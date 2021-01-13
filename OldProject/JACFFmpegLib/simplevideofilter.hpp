#ifndef SIMPLEFILTER_HPP
#define SIMPLEFILTER_HPP

#include "common.hpp"
#include "frame.hpp"

namespace JACFFmpegLib
{
    class SimpleVideoFilter
    {
    private:
        AVFilterGraph *filterGraph = nullptr;
        AVFilterContext *bufferSource = nullptr;
        AVFilterContext *bufferSink = nullptr;

    public:
        JACFFMPEGLIB_EXPORT SimpleVideoFilter(string filterGraphString,
                     int inputWidth,
                     int inputHeight,
                     AVPixelFormat inputFormat,
                     AVRational inputTimebase,
                     AVRational inputStaticAspectRatio = {0, 1},
                     optional<AVRational> inputFramerate = std::nullopt);

        JACFFMPEGLIB_EXPORT SimpleVideoFilter(string filterGraphString, Frame& configureFrame);
        JACFFMPEGLIB_EXPORT ~SimpleVideoFilter();

        JACFFMPEGLIB_EXPORT FrameList filterFrame(Frame& frame);
    };
}

#endif // SIMPLEFILTER_HPP
