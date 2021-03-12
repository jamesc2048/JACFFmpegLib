
#include "JACFFmpegLib.hpp"

#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

std::string_view url = "/mnt/c/Users/James Crisafulli/Videos/2021-01-12 14-45-20.mkv";

TEST_CASE("InputUrl") 
{
	av_log_set_level(AV_LOG_TRACE);

	InputUrl input{ url };

	CHECK(input.url() == url);

	FramePtr fr = input.nextFrame();
}