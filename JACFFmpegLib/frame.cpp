#include "frame.hpp"

namespace JACFFmpegLib
{
    Frame::Frame()
    {
        frame = make_avframe(av_frame_alloc());
    }

    Frame::Frame(AVFrame *frame)
                : Frame(make_avframe(frame))
    {

    }

    Frame::Frame(AVFramePtr frame)
                : frame(move(frame))
    {
    }

    Frame::~Frame()
    {
    }

    vector<uint8_t> Frame::dumpToBytes()
    {
        AVFramePtr& fr = getAVFrame();

        vector<uint8_t> vec;

        switch (fr->format)
        {
            case AVPixelFormat::AV_PIX_FMT_YUV420P:
                for (int y = 0; y < fr->height; y++)
                {
                    uint8_t* lineStart = fr->data[0] + fr->linesize[0] * y;

                    for (int x = 0; x < fr->width; x++)
                    {
                        vec.push_back(*(lineStart + x));
                    }
                }

                for (int y = 0; y < fr->height / 2; y++)
                {
                    uint8_t* lineStart = fr->data[1] + fr->linesize[1] * y;

                    for (int x = 0; x < fr->width / 2; x++)
                    {
                        vec.push_back(*(lineStart + x));
                    }
                }

                for (int y = 0; y < fr->height / 2; y++)
                {
                    uint8_t* lineStart = fr->data[2] + fr->linesize[2] * y;

                    for (int x = 0; x < fr->width / 2; x++)
                    {
                        vec.push_back(*(lineStart + x));
                    }
                }

                break;

            default:
                THROW_EXCEPTION("Not implemented");
        }

        return vec;
    }

    AVFramePtr & Frame::getAVFrame()
    {
        // Needed for internal operations. Hidden to external API.
        return frame;
    }
}
