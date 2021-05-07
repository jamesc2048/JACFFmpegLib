#pragma once

#include "frame.hpp"

class AudioFrame : public Frame
{
	// Disallow copy, use clone method
	AudioFrame(const AudioFrame& fr) = delete;
	AudioFrame& operator= (const AudioFrame&) = delete;

	~AudioFrame() override
	{
	}

	AVMediaType type() override
	{
		return AVMEDIA_TYPE_AUDIO;
	}
};

using AudioFramePtr = std::unique_ptr<AudioFrame>;