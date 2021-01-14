#pragma once

#include <string>

// TODO is this correct?
#ifdef JACFFMPEGLIB_BUILD
	#define EXPORT __declspec(dllexport)

extern "C" {
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
}
#else
	#define EXPORT //__declspec(dllimport)
#endif

enum class FFmpegError
{
	NoError,
	DemuxerError,
	NoStreams,
	CodecError,
};

class EXPORT InputURL
{
private:
#ifdef JACFFMPEGLIB_BUILD
	std::string url;
	bool isOpen = false;
	
	AVFormatContext* formatCtx = nullptr;
	AVCodecContext* codecCtx = nullptr;
#endif

public:
	InputURL(std::string url);
	~InputURL();

	FFmpegError open();
	void close();

	std::string getUrl();
	bool getIsOpen();
};