#ifndef JACFFMPEGLIB_GLOBAL_HPP
#define JACFFMPEGLIB_GLOBAL_HPP

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define Q_DECL_EXPORT __declspec(dllexport)
#  define Q_DECL_IMPORT __declspec(dllimport)
#else
#  define Q_DECL_EXPORT     __attribute__((visibility("default")))
#  define Q_DECL_IMPORT     __attribute__((visibility("default")))
#endif

#if defined(JACFFMPEGLIB_LIBRARY)
#  define JACFFMPEGLIB_EXPORT Q_DECL_EXPORT
#else
#  define JACFFMPEGLIB_EXPORT Q_DECL_IMPORT
#endif

extern "C"
{
    #include "libavformat/avformat.h"
    #include "libavcodec/avcodec.h"
    #include "libavutil/avutil.h"
    #include "libavfilter/avfilter.h"
    #include "libswscale/swscale.h"
    #include "libswresample/swresample.h"
}

#endif // JACFFMPEGLIB_GLOBAL_HPP
