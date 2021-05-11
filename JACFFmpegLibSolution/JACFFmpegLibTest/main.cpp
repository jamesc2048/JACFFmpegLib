
#include "JACFFmpegLib.hpp"

#include <memory>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("InputUrl")
{
	std::string url = "/mnt/d/secureReturn 2020-06-14 12_37-38671263712.mp4";

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

		REQUIRE(fr);

		if (fr->type() == AVMEDIA_TYPE_VIDEO)
		{
			break;
		}
	}

	// TODO factory function to cast pointer
	VideoFrame* videoFrame = (VideoFrame*)fr.get();

	CHECK(videoFrame->width() == 720);
	CHECK(videoFrame->height() == 576);
	CHECK(videoFrame->format() == AV_PIX_FMT_YUV420P);
}

TEST_CASE("InputUrl-NonExistant")
{
	std::string url = "fileWhichDoesntExist";

	std::unique_ptr<InputUrl> input;

	REQUIRE_THROWS(input = std::make_unique<InputUrl>(url));
}