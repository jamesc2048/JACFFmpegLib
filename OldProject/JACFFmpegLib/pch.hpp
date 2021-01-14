#ifndef PCH_H
#define PCH_H

#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <optional>
#include <thread>
#include <cassert>

extern "C"
{
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/avutil.h>
    #include <libavfilter/avfilter.h>
    #include <libswscale/swscale.h>
    #include <libswresample/swresample.h>

    #include <libavutil/imgutils.h>
    #include <libavfilter/buffersrc.h>
    #include <libavfilter/buffersink.h>
}

#include "utilities.hpp"

#endif // PCH_H