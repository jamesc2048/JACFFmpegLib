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
};
