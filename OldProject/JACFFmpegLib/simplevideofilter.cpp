#include "simplevideofilter.hpp"

namespace JACFFmpegLib
{
    SimpleVideoFilter::SimpleVideoFilter(string filterGraphString,
                               int inputWidth,
                               int inputHeight,
                               AVPixelFormat inputFormat,
                               AVRational inputTimebase,
                               AVRational inputStaticAspectRatio,
                               optional<AVRational> inputFramerate)
    {
        stringstream fullFilterString;
        fullFilterString << "buffer=video_size=" << inputWidth << "x" << inputHeight <<
                                                    ":pix_fmt=" << inputFormat <<
                                                    ":time_base=" << inputTimebase.num << "/" << inputTimebase.den <<
                                                    ":pixel_aspect=" << inputStaticAspectRatio.num << "/" << inputStaticAspectRatio.den;


        if (inputFramerate.has_value())
        {
            AVRational fr = inputFramerate.value();
            fullFilterString << ":frame_rate=" << fr.num << "/" << fr.den;
        }

        fullFilterString << "," << filterGraphString << ",buffersink";

        AVFilterInOut *input = nullptr;
        AVFilterInOut *output = nullptr;

        filterGraph = avfilter_graph_alloc();

        if (!filterGraph)
        {
            THROW_EXCEPTION("Could not allocate filter graph");
        }

        int ret = avfilter_graph_parse2(filterGraph, filterGraphString.c_str(), &input, &output);

        if (ret < 0)
        {
            THROW_EXCEPTION("Failed to parse and generate filters for filterString: %d, %s");
        }

        // TODO filter in/out can be used to configure complex filter
        // EG [in0][in1]hstack=inputs=2[out0]; [in2]null[out1]
        // produces input of in0, in1 with filtergraph hstack, and in2 with filtergraph null
        // output out0 and out1
        // Should be as simple as attaching buffersrc to each input, and buffersink to each output

        avfilter_inout_free(&input);
        avfilter_inout_free(&output);

        for (uint32_t i = 0; i < filterGraph->nb_filters; ++i)
        {
            AVFilterContext* ctx = filterGraph->filters[i];

            if (ctx->nb_inputs == 0)
            {
                bufferSource = ctx;
            }
            else if (ctx->nb_outputs == 0)
            {
                bufferSink = ctx;
            }
        }

        ret = avfilter_graph_config(filterGraph, nullptr);

        if (ret < 0)
        {
            THROW_EXCEPTION("Failed to configure filter graph: %d, %s");
        }

        avfilter_graph_dump(filterGraph, nullptr);
    }

    SimpleVideoFilter::SimpleVideoFilter(string filterGraphString, Frame& fr)
                : SimpleVideoFilter(filterGraphString,
                               (int)fr.width(),
                               (int)fr.height(),
                               fr.pixelFormat(),
                               fr.timebase(),
                               fr.sampleAspectRatio())
    {
    }

    SimpleVideoFilter::~SimpleVideoFilter()
    {
        if (filterGraph)
        {
            avfilter_graph_free(&filterGraph);
        }
    }


    FrameList SimpleVideoFilter::filterFrame(Frame& frame)
    {
        int ret = av_buffersrc_add_frame_flags(bufferSource, frame.avframe().get(), AV_BUFFERSRC_FLAG_PUSH);

        if (ret < 0)
        {
            THROW_EXCEPTION("Could not add frame to buffersrc: %d");
        }

        FrameList frameList;

        while (true)
        {
            Frame filteredFrame;
            ret = av_buffersink_get_frame(bufferSink, filteredFrame.avframe().get());

            if (ret == AVERROR(EAGAIN))
            {
                break;
            }
            else if (ret == AVERROR_EOF)
            {
                // TODO signal that sink is closed with a flag? I'm not sure that buffersink can actually flag this.
                break;
            }
            else if (ret < 0)
            {
                THROW_EXCEPTION("Could not pull frame from buffersink: %d");
            }
            else
            {
                frameList.emplace_back(move(filteredFrame));
                frameList.back().setMediaType(AVMediaType::AVMEDIA_TYPE_VIDEO);
                frameList.back().setTimebase(av_buffersink_get_time_base(bufferSink));
            }
        }

        return frameList;
    }
}
