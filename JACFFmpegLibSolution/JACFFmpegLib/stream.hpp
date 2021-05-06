#pragma once

#include "pch.hpp"

enum class StreamType
{
	Unknown = AVMEDIA_TYPE_UNKNOWN,
	Video = AVMEDIA_TYPE_VIDEO,
	Audio = AVMEDIA_TYPE_AUDIO
};

class Stream
{
	using StreamPtr = std::unique_ptr<Stream>;

private:
	Stream(const Stream&) = delete;
	Stream& operator=(const Stream&) = delete;

protected:
	AVStream* avstream = nullptr;
	
	Stream() = default;

public:
	StreamType streamType();

	static StreamPtr make(AVStream* stream);

	virtual ~Stream() 
	{
	}
};

using StreamPtr = std::unique_ptr<Stream>;

class VideoStream : public Stream
{
private:

public:
	VideoStream(AVStream* stream) : Stream()
	{
		avstream = stream;
	}

	~VideoStream() override
	{
	}
};

class AudioStream : public Stream
{
private:

public:
	AudioStream(AVStream* stream) : Stream()
	{
		avstream = stream;
	}

	~AudioStream() override
	{
	}
};