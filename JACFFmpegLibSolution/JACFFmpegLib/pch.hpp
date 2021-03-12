#pragma once

// C++ stdlib
#include <cstdint>
#include <string> 
#include <memory> 
#include <exception>
#include <vector>

// FFmpeg headers
extern "C" {
#include <libavutil/avutil.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}