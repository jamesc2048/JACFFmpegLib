#pragma once

#include "pch.hpp"
#include "utils.hpp"

class Frame
{
	using FramePtr = std::unique_ptr<Frame>;

private:
	AVFramePtr avframe;

	Frame() = delete;

public:
	Frame(AVFramePtr&& fr)
	{
		avframe = std::move(fr);
	}

	virtual ~Frame()
	{
	}

	// Disallow copy, use clone method
	Frame(const Frame& fr) = delete;
	Frame& operator=(const Frame&) = delete;

	FramePtr clone()
	{
		// TODO copy frame with av_frame_copy()
		//return Frame
		return {};
	}
};

using FramePtr = std::unique_ptr<Frame>;
