#pragma once

#include "stream.hpp"
#include "frame.hpp"

class VideoStream : public Stream
{
private:

public:
	VideoStream(AVStream* stream) :
		Stream(stream)
	{
	}

	// AVStream video properties
	int width()
	{
		return avstream->codecpar->width;
	}

	int height()
	{
		return avstream->codecpar->height;
	}

	AVPixelFormat format()
	{
		return static_cast<AVPixelFormat>(avstream->codecpar->format);
	}

	~VideoStream() override
	{
	}
};

