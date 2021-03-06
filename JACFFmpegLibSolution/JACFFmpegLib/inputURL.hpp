#pragma once

#include "pch.hpp"

#include "frame.hpp"
#include "stream.hpp"
#include "utils.hpp"

#include <stdexcept>
#include <sstream>
#include <cstdio>

class InputUrl
{
private:
	AVFormatContext* mFormatCtx = nullptr;
	std::vector<StreamPtr> mStreams;

public:
	InputUrl(std::string url)
	{
		using namespace std::string_literals;

		// Open and read format 
		if (int ret = avformat_open_input(&mFormatCtx, url.c_str(), nullptr, nullptr); ret < 0)
		{
			throw FFmpegException(format("Could not open URL \"%s\"", url.c_str()), ret);
		}

		if (int ret = avformat_find_stream_info(mFormatCtx, nullptr); ret < 0)
		{
			throw FFmpegException(format("Could not find stream info for URL \"%s\"", url.c_str()), ret);
		}

		// Open codecs and create Stream wrapper.
		for (uint32_t i = 0; i < mFormatCtx->nb_streams; i++)
		{
			try
			{
				StreamPtr streamPtr = Stream::make(mFormatCtx->streams[i]);

				mStreams.emplace_back(std::move(streamPtr));
			}
			catch (...)
			{
				throw;
			}
		}

		// Streams are opened and configured.
	}

	~InputUrl()
	{
		avformat_close_input(&mFormatCtx);
	}

	std::string_view url()
	{
		return mFormatCtx->url;
	}

	const std::vector<StreamPtr>& streams()
	{
		return mStreams;
	}

	FramePtr nextFrame()
	{
		PacketPtr packet(av_packet_alloc());
		packet->size = 0;
		packet->data = nullptr;

		int ret = av_read_frame(mFormatCtx, packet.get());

		switch (ret)
		{
			// 0 if OK, < 0 on error or end of file
		case 0:
			break;

		case AVERROR_EOF:
			// set EOF flag
			break;

		default:
			// unknown error
			throw std::runtime_error("");
		}

		// TODO send to appropriate stream
		//StreamPtr& stream = streams[packet.stream_index];

		//stream->decode(std::move(packet));

		return {};
	}
};
