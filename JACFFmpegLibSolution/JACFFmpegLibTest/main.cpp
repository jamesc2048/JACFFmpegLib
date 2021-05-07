
#include "JACFFmpegLib.hpp"

#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("InputUrl")
{
	std::string url = "Test/testFile.mp4";

	av_log_set_level(AV_LOG_TRACE);

	std::unique_ptr<InputUrl> input;

	REQUIRE_NOTHROW(input = std::make_unique<InputUrl>(url));

	CHECK(input->url() == url);
	CHECK(input->streams().size() == 2);

	FramePtr fr;
	
	// TODO check for EOF
	while (true)
	{
		fr = input->nextFrame();

		if (fr->type() == 0)
		{
			break;
		}
	}

	REQUIRE(fr);

	//VideoFramePtr

	CHECK(fr->width() == 720);
	CHECK(fr->height() == 576);
	CHECK(fr->format() == AV_PIX_FMT_YUV420P);
}

TEST_CASE("InputUrl-NonExistant")
{
	std::string url = "fileWhichDoesntExist";

	std::unique_ptr<InputUrl> input;

	REQUIRE_THROWS(input = std::make_unique<InputUrl>(url));
}