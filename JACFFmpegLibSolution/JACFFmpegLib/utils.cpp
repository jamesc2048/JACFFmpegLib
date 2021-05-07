#include "utils.hpp"

FFmpegException::FFmpegException(const std::string& what, int avError) 
	: std::runtime_error(what)
{
	char avErrorStr[AV_ERROR_MAX_STRING_SIZE];

	if (av_strerror(avError, avErrorStr, sizeof avErrorStr) != 0)
	{
		snprintf(avErrorStr, sizeof avErrorStr, "Unknown AVError");
	}

	exceptionText = format("FFmpeg error: %s. Return code: %d, %s", what.c_str(), avError, avErrorStr);
}

std::string format(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	char buf[256];

	if (vsnprintf(buf, sizeof buf, format, args) > 0)
	{
		std::string result = buf;

		return result;
	}

	return {};
}