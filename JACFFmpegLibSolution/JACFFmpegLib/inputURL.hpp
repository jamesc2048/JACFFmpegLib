#pragma once

#include "pch.hpp"

#include "frame.hpp"

class InputUrl
{
private:
	// av format ctx
	AVFormatContext* formatCtx = nullptr;
	AVCodecContext* codecCtx = nullptr;

public:
	InputUrl(std::string_view url)
	{
		using namespace std::string_literals;

		int ret = avformat_open_input(&formatCtx, url.data(), nullptr, nullptr);

		if (ret < 0)
		{
			// 0 on success, a negative AVERROR on failure.
			char errString[1024];
			std::vsnprintf(errString, sizeof errString, "Could not open URL \"%s\", ret %d", url.data(), ret);
			throw std::runtime_error(errString);
		}

		ret = avformat_find_stream_info(formatCtx, nullptr);

		if (ret < 0)
		{
			// >= 0 if OK, AVERROR_xxx on error
			char errString[1024];
			std::vsnprintf(errString, sizeof errString, "Could not find stream info for URL \"%s\", ret %d", url.data(), ret);
			throw std::runtime_error(errString);
		}

		for (int i = 0; i < formatCtx->nb_streams; i++)
		{
			const AVStream* stream = formatCtx->streams[i];

			
		}
	}

	~InputUrl()
	{
		// close input format ctx
		avformat_close_input(&formatCtx);
	}

	std::string_view url()
	{
		return formatCtx->url;
	}

	FramePtr nextFrame()
	{
		AVPacket packet;
		av_init_packet(&packet);
		packet.size = 0;
		packet.data = nullptr;

		int ret = av_read_frame(formatCtx, &packet);

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

		ret = avcodec_send_packet(codecCtx, &packet);

		switch (ret)
		{
			case 0:
				break;
			case AVERROR(EAGAIN): 
				break;						// output is not available in this state - user must try to send new input
			case AVERROR_EOF:
				break;						// the decoder has been fully flushed, and there will be no more output frames
			case AVERROR(EINVAL):
				break;						// codec not opened, or it is an encoder
			case AVERROR_INPUT_CHANGED:
				break;						// current decoded frame has changed parameters with respect to first decoded frame. Applicable when flag AV_CODEC_FLAG_DROPCHANGED is set.
			default:
				throw std::runtime_error(""); // other negative values : legitimate decoding errors
		}


		return {};
	}
};
