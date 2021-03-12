#pragma once

#include "pch.hpp"

enum class FrameType
{
	Unknown = AVMEDIA_TYPE_UNKNOWN,
	Video = AVMEDIA_TYPE_VIDEO,
	Audio = AVMEDIA_TYPE_AUDIO
};

struct AVFrameDeleter
{
	void operator()(AVFrame* fr)
	{
		if (fr)
		{
			av_frame_free(&fr);
		}
	}
};

struct AVPacketDeleter
{
	void operator()(AVPacket* p)
	{
		if (p)
		{
			av_packet_free(&p);
		}
	}
};

using PacketPtr = std::unique_ptr<AVPacket, AVPacketDeleter>;
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

	~VideoFrame() override
	{
	}
};

class AudioFrame : public Frame
{
	// Disallow copy, use clone method
	AudioFrame(const AudioFrame& fr) = delete;
	AudioFrame& operator= (const AudioFrame&) = delete;

	~AudioFrame() override
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