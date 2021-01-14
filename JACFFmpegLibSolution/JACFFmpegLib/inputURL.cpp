#include "inputURL.hpp"

#include <iostream>

InputURL::InputURL(std::string url) :
	url(url)
{
}

InputURL::~InputURL()
{
	close();
}

FFmpegError InputURL::open()
{
	std::cout << "opening " << url << std::endl;

	int ret;

	if (ret = avformat_open_input(&formatCtx, url.c_str(), nullptr, nullptr))
	{
		return FFmpegError::DemuxerError;
	}

	if (ret = avformat_find_stream_info(formatCtx, nullptr))
	{
		close();
		return FFmpegError::DemuxerError;
	}

	if (formatCtx->nb_streams == 0)
	{
		close();
		return FFmpegError::NoStreams;
	}

	av_dump_format(formatCtx, 0, url.c_str(), 0);

	isOpen = true;
	return FFmpegError::NoError;
}

void InputURL::close()
{
	std::cout << "opening " << url << std::endl;

	avformat_close_input(&formatCtx);
	avcodec_free_context(&codecCtx);

	isOpen = false;
}

std::string InputURL::getUrl()
{
	return url;
}

bool InputURL::getIsOpen()
{
	return isOpen;
}