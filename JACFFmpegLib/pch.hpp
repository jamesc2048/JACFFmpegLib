#ifndef PCH_H
#define PCH_H

#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <optional>

extern "C"
{
    #include "libavformat/avformat.h"
    #include "libavcodec/avcodec.h"
    #include "libavutil/avutil.h"
    #include "libavfilter/avfilter.h"
    #include "libswscale/swscale.h"
    #include "libswresample/swresample.h"
}

#include "utilities.hpp"

#endif // PCH_H
