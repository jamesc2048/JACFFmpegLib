#pragma once

#include "frame.hpp"

class VideoFrame : public Frame
{
	// Disallow copy, use clone method
	VideoFrame(const VideoFrame& fr) = delete;
	VideoFrame& operator= (const VideoFrame&) = delete;

	~VideoFrame() override
	{
	}
};