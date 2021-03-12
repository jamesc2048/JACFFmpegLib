#pragma once

// C++ stdlib
#include <string> 
#include <memory> 
#include <exception>

// FFmpeg headers
extern "C" {
#include <libavutil/avutil.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}