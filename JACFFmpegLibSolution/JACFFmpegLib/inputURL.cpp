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

	int ret = avformat_open_input(&formatCtx, url.c_str(), nullptr, nullptr);

	std::cout << ret << std::endl;

	if (ret < 0)
	{
		return FFmpegError::DemuxerError;
	}

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