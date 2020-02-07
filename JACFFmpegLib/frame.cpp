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
            THROW_EXCEPTION("Only implemented for video data");
        }

        vector<uint8_t> vec;

        // No special alignment: align to byte
        const int alignment = 8;

        // Read this with "ffplay -video_size widthxheight -pixel_format format"
        int bufSize = av_image_get_buffer_size((AVPixelFormat)fr->format,
                                               fr->width,
                                               fr->height,
                                               alignment);
        vec.resize((size_t)bufSize);

        int ret = av_image_copy_to_buffer(vec.data(),
                                          bufSize,
                                          fr->data,
                                          fr->linesize,
                                          (AVPixelFormat)fr->format,
                                          fr->width,
                                          fr->height,
                                          alignment);

        if (ret == AVERROR(EINVAL))
        {
            THROW_EXCEPTION("Frame format not supported");
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

    AVRational Frame::sampleAspectRatio()
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_VIDEO);

        return _frame->sample_aspect_ratio;
    }

    AVSampleFormat Frame::sampleFormat()
    {
        CHECK_MEDIA_TYPE(AVMediaType::AVMEDIA_TYPE_AUDIO);

        return (AVSampleFormat)_frame->format;
    }

    AVFramePtr& Frame::avframe()
    {
        return _frame;
    }
}
