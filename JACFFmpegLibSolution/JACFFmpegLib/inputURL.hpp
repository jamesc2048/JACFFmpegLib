#pragma once

#include "pch.hpp"

#include "frame.hpp"
#include "stream.hpp"

class InputUrl
{
private:
	// av format ctx
	AVFormatContext* mFormatCtx = nullptr;
	std::vector<StreamPtr> mStreams;

public:
	InputUrl(std::string_view url)
	{
		using namespace std::string_literals;

		// Open format
		int32_t ret = avformat_open_input(&mFormatCtx, url.data(), nullptr, nullptr);

		if (ret < 0)
		{
			// 0 on success, a negative AVERROR on failure.
			char errString[1024];
			std::snprintf(errString, sizeof errString, "Could not open URL \"%s\", ret %d", url.data(), ret);
			throw std::runtime_error(errString);
		}

		// Get stream info
		ret = avformat_find_stream_info(mFormatCtx, nullptr);

		if (ret < 0)
		{
			// >= 0 if OK, AVERROR_xxx on error
			char errString[1024];
			std::snprintf(errString, sizeof errString, "Could not find stream info for URL \"%s\", ret %d", url.data(), ret);
			throw std::runtime_error(errString);
		}

		// Open codecs
		for (uint32_t i = 0; i < mFormatCtx->nb_streams; i++)
		{
			StreamPtr streamPtr = Stream::make(mFormatCtx->streams[i]);

			if (!streamPtr)
			{
				char errString[1024];
				std::snprintf(errString, sizeof errString, "Could create stream %d for URL \"%s\", ret %d", i, url.data(), ret);
				throw std::runtime_error(errString);
			}

			mStreams.emplace_back(std::move(streamPtr));
		}
	}

	~InputUrl()
	{
		// close input format ctx
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
		PacketPtr packet = PacketPtr(av_packet_alloc());
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
			throw std::runtime_error("");
		}

		// TODO send to appropriate stream
		//StreamPtr& stream = streams[packet.stream_index];

		//stream->decode(std::move(packet));

		return {};
	}
};
