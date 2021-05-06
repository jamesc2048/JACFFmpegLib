#include "stream.hpp"

StreamType Stream::streamType()
{
	return (StreamType)avstream->codecpar->codec_type;
}

StreamPtr Stream::make(AVStream* avstream)
{
	if (!avstream)
	{
		return {};
	}

	StreamPtr stream;

	switch (avstream->codecpar->codec_type)
	{
	case AVMEDIA_TYPE_VIDEO:
		stream = std::make_unique<VideoStream>(avstream);
		break;

	case AVMEDIA_TYPE_AUDIO:
		stream = std::make_unique<AudioStream>(avstream);
		break;

	default:
		return {};
	}


	return stream;
}
