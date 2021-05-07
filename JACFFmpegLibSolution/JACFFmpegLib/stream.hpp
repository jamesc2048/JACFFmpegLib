#pragma once

#include "pch.hpp"

class Stream
{
	using StreamPtr = std::unique_ptr<Stream>;

private:
	Stream(const Stream&) = delete;
	Stream& operator=(const Stream&) = delete;

protected:
	AVStream* avstream = nullptr;
	
	Stream(AVStream* stream)
	{
		avstream = stream;
	}

public:
	// AVStream common properties
	AVMediaType type()
	{
		return avstream->codecpar->codec_type;
	}

	int index()
	{
		return avstream->index;
	}

	int bitRate()
	{
		return avstream->codecpar->bit_rate;
	}

	static StreamPtr make(AVStream* stream);

	virtual ~Stream() 
	{
	}
};

using StreamPtr = std::unique_ptr<Stream>;

// TODO other stream types