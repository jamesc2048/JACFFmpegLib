#pragma once

// C stdlib
#include <cassert>
#include <cstdint>

// C++ stdlib
#include <string> 
#include <memory> 
#include <exception>
#include <vector>

// FFmpeg warnings for MSVC in headers
// warning C4244: 'return': conversion from 'int' to 'uint8_t', possible loss of data
#pragma warning(push)
#pragma warning(disable: 4244)

// FFmpeg headers
extern "C" 
{
	#include <libavutil/avutil.h>
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
}

#pragma warning(pop)