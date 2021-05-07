#pragma once

#include "stream.hpp"

class AudioStream : public Stream
{
private:

public:
	AudioStream(AVStream* stream) :
		Stream(stream)
	{
	}

	// AVStream audio properties
	AVSampleFormat format()
	{
		return static_cast<AVSampleFormat>(avstream->codecpar->format);
	}

	~AudioStream() override
	{
	}
};