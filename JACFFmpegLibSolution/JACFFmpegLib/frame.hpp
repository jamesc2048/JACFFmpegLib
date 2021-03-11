#pragma once

#include "pch.hpp"

struct AVFrame;

struct AVFrameDeleter
{
	void operator()(AVFrame* fr)
	{
		if (fr)
		{
			//av_frame_free(fr);
		}
	}
};

using AVFramePtr = std::unique_ptr<AVFrame, AVFrameDeleter>;

class Frame
{
private:
	AVFramePtr avframe;

public:
	Frame()
	{
	}

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

	Frame clone()
	{
		// TODO copy frame with av_frame_copy()
		//return Frame
		return {};
	}


};

using FramePtr = std::unique_ptr<Frame>;

class VideoFrame : public Frame
{
	// Disallow copy, use clone method
	VideoFrame(const VideoFrame& fr) = delete;
	VideoFrame& operator= (const VideoFrame&) = delete;

	virtual ~VideoFrame()
	{
	}
};

class AudioFrame : public Frame
{
	// Disallow copy, use clone method
	AudioFrame(const AudioFrame& fr) = delete;
	AudioFrame& operator= (const AudioFrame&) = delete;

	virtual ~AudioFrame()
	{
	}
};

// TODO
//class SubtitleFrame : Frame
//{
//	
//};

// TODO
//class DataFrame : Frame
//{
//
//};