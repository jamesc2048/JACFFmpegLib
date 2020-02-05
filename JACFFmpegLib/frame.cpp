#include "frame.hpp"

namespace JACFFmpegLib
{
    Frame::Frame()
    {
        _frame = make_avframe(av_frame_alloc());
    }

    Frame::Frame(AVFrame *frame)
                : Frame(make_avframe(frame))
    {

    }

    Frame::Frame(AVFramePtr frame)
                : _frame(move(frame))
    {
    }

    Frame::~Frame()
    {
    }

    vector<uint8_t> Frame::dumpToBytes()
    {
        AVFramePtr& fr = avframe();

        if (mediaType() != AVMediaType::AVMEDIA_TYPE_VIDEO)
        {
            THROW_EXCEPTION("Not implemented");
        }

        vector<uint8_t> vec;

        switch (fr->format)
        {
            case AVPixelFormat::AV_PIX_FMT_YUV420P:
            {
                assert(fr->width > 0 && fr->height > 0);

                // Read this with "ffplay -video_size widthxheight -pixel_format yuv420p"
                // 8bpp Y + 2bpp U + 2bpp V
                size_t wh = fr->width * fr->height;
                vec.resize(wh + wh / 2);
                uint8_t* vecData = vec.data();

                for (int y = 0; y < fr->height; y++)
                {
                    uint8_t* lineStart = fr->data[0] + fr->linesize[0] * y;

                    memcpy(vecData, lineStart, fr->width);
                    vecData += fr->width;
                }

                for (int y = 0; y < fr->height / 2; y++)
                {
                    uint8_t* lineStart = fr->data[1] + fr->linesize[1] * y;

                    memcpy(vecData, lineStart, fr->width / 2);
                    vecData += fr->width / 2;
                }

                for (int y = 0; y < fr->height / 2; y++)
                {
                    uint8_t* lineStart = fr->data[2] + fr->linesize[2] * y;

                    memcpy(vecData, lineStart, fr->width / 2);
                    vecData += fr->width / 2;
                }

                break;
            }

            default:
                THROW_EXCEPTION("Not implemented");
        }

        return vec;
    }

    void Frame::setMediaType(AVMediaType mediaType)
    {
        _mediaType = mediaType;
    }

    AVMediaType Frame::mediaType()
    {
        return _mediaType;
    }

    void Frame::setTimebase(AVRational timebase)
    {
        _timebase = timebase;
    }

    AVRational Frame::timebase()
    {
        return _timebase;
    }

    int64_t Frame::timestamp()
    {
        return _frame->pts;
    }

    double Frame::timestampSeconds()
    {
        AVRational tb = timebase();

        if (tb.den > 0)
        {
            return Utils::timestampToSeconds(_frame->pts, timebase());
        }
        else
        {
            THROW_EXCEPTION("Invalid timebase on Frame");
        }
    }

    size_t Frame::width()
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return _frame->width;
    }

    size_t Frame::height()
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return _frame->height;
    }

    AVPixelFormat Frame::pixelFormat()
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return (AVPixelFormat)_frame->format;
    }

    AVSampleFormat Frame::sampleFormat()
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_AUDIO);

        return (AVSampleFormat)_frame->format;
    }

    AVFramePtr & Frame::avframe()
    {
        // Needed for internal operations. Hidden to external API.
        return _frame;
    }
}
