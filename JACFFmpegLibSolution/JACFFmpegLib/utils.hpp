#pragma once

#include "pch.hpp"

struct AVFrameDeleter
{
	void operator()(AVFrame* fr)
	{
		if (fr)
		{
			av_frame_free(&fr);
		}
	}
};

struct AVPacketDeleter
{
	void operator()(AVPacket* p)
	{
		if (p)
		{
			av_packet_free(&p);
		}
	}
};

using PacketPtr = std::unique_ptr<AVPacket, AVPacketDeleter>;
using AVFramePtr = std::unique_ptr<AVFrame, AVFrameDeleter>;

std::string format(const char* format, ...);

class FFmpegException : public std::runtime_error
{
private:
	std::string exceptionText;

public:
	FFmpegException() = delete;
	FFmpegException(const std::string& what) = delete;

	FFmpegException(const std::string& what, int avError);
	virtual ~FFmpegException() = default;

	virtual const char* what() const noexcept override
	{
		return exceptionText.c_str();
	}
};