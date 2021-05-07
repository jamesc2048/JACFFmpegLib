#include "stream.hpp"
#include "videoStream.hpp"
#include "audioStream.hpp"


StreamPtr Stream::make(AVStream* avstream)
{
	assert(avstream != nullptr);

	StreamPtr stream = {};

	switch (avstream->codecpar->codec_type)
	{
	case AVMEDIA_TYPE_VIDEO:
		stream = std::make_unique<VideoStream>(avstream);
		break;

	case AVMEDIA_TYPE_AUDIO:
		stream = std::make_unique<AudioStream>(avstream);
		break;

	default:
		// TODO other stream types
		break;
	}

	return stream;
}
