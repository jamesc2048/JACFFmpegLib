#include "jacffmpeglib.hpp"

JACFFmpegLib::JACFFmpegLib()
{

}

std::string JACFFmpegLib::test()
{
    AVFormatContext *formatCtx = nullptr;

    const char* url = "D:\\testXml_2.mp4";
    int r = avformat_open_input(&formatCtx, url, nullptr, nullptr);

    if (r < 0 || !formatCtx)
    {
        // error
        return "error!";
    }

    av_dump_format(formatCtx, -1, url, false);
    return std::to_string(formatCtx->duration);
}
