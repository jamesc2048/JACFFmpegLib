
#include "JACFFmpegLib.hpp"

#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

std::string url = "/mnt/c/Users/James Crisafulli/Videos/2021-01-12 14-45-20a.mkv";

TEST_CASE("InputUrl") 
{
	av_log_set_level(AV_LOG_TRACE);

	std::unique_ptr<InputUrl> input;
	
	REQUIRE_NOTHROW(input = std::make_unique<InputUrl>(url));

	CHECK(input->url() == url);
	CHECK(input->streams().size() == 2);

	FramePtr fr = input->nextFrame();
}