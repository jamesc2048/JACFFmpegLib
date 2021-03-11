#pragma once

#include <string>
#include <memory>

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
	AVFormatContext* formatCtx = nullptr;
	AVCodecContext* codecCtx = nullptr;

	std::string url;
	bool isOpen = false;
#endif
	
	InputURL();

public:
	static std::unique_ptr<InputURL> create(std::string url);
	~InputURL();

	void close();

	// Getters
	std::string getUrl();

};