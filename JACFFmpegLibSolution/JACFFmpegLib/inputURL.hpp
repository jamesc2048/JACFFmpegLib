#pragma once

#include "pch.hpp"

#include "frame.hpp"

class InputUrl
{
private:
	std::string mUrl;
	// av format ctx

public:
	InputUrl(std::string_view url) : mUrl(url)
	{
		// open format context
		// throw if can't open
	}

	~InputUrl()
	{
		// close input format ctx
	}

	const std::string& url()
	{
		return mUrl;
	}

	FramePtr nextFrame()
	{
		return {};
	}
};
