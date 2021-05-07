#pragma once

#include "pch.hpp"
#include "frame.hpp"

class VideoFrame : public Frame
{
	// Disallow copy, use clone method
	VideoFrame(const VideoFrame& fr) = delete;
	VideoFrame& operator= (const VideoFrame&) = delete;

	~VideoFrame() override
	{
	}

public:
	AVMediaType type() override
	{
		return AVMEDIA_TYPE_VIDEO;
	}

	int width()
	{
		return avframe->width;
	}

	int height()
	{
		return avframe->height;
	}

	AVPixelFormat format()
	{
		return static_cast<AVPixelFormat>(avframe->format);
	}
};

using VideoFramePtr = std::unique_ptr<VideoFrame>;