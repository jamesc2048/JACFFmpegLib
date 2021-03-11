// TestProject.cpp : Defines the entry point for the application.
//

#include "testProject.hpp"

#include "..\JACFFmpegLib\inputURL.hpp"

int main()
{
	InputURL url("D:\\wow.mp4");

	FFmpegError err = url.open();

	std::cout << "wow" << std::endl;
}
