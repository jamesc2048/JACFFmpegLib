#include <JACFFmpegLib.hpp>

using namespace JACFFmpegLib;

#include <string>
#include <QtCore>
#include <iostream>
#include <fstream>

void videoDecodeDumpFrames()
{
    int count = 0;
    int64_t startMs = QDateTime::currentMSecsSinceEpoch();

    QFile f("D:\\dump.yuv");
    f.open(QIODevice::WriteOnly);

    try
    {
        unique_ptr<Demuxer> demuxer = make_unique<Demuxer>("D:\\1hourPAL.mp4");

        unique_ptr<VideoDecoder> decoder;

        while (!demuxer->isEOS())
        {
            Packet p = demuxer->nextPacket();

            if (p.hasData() && p.mediaType() == AVMediaType::AVMEDIA_TYPE_VIDEO)
            {
                if (!decoder)
                {
                    if (shared_ptr<Stream> stream = p.streamRef().lock())
                    {
                        decoder = make_unique<VideoDecoder>(*stream);
                    }
                    else
                    {
                        throw std::runtime_error("Demuxer not present");
                    }
                }

                FrameList frames = decoder->decodePacket(p);

                for (auto &fr : frames)
                {
                    count++;
                    auto vec = fr.dumpToBytes();
                    f.write((const char *)vec.data(), vec.size());
                    //qDebug() << fr.timestampSeconds();
                }
            }
        }

        FrameList remainingFrames = decoder->drain();

        for (auto& fr : remainingFrames)
        {
            count++;
            auto vec = fr.dumpToBytes();
            f.write((const char *)vec.data(), vec.size());
            //qDebug() << fr.timestampSeconds();
        }

    }
    catch (const std::exception &e)
    {
        qDebug() << "exception: " << e.what();
    }

    double elapsed = (QDateTime::currentMSecsSinceEpoch() - startMs) / 1000.;
    qInfo() << "Finished " << count << " frames in " << elapsed << " FPS: " << count / elapsed;
}


void videoDecodeBenchmark()
{
    int count = 0;
    int64_t startMs = QDateTime::currentMSecsSinceEpoch();

    try
    {
        unique_ptr<Demuxer> demuxer = make_unique<Demuxer>("D:\\1hourPAL.mp4");

        unique_ptr<VideoDecoder> decoder;
        unique_ptr<SimpleVideoFilter> filter;

        while (!demuxer->isEOS())
        {
            Packet p = demuxer->nextPacket();

            if (p.hasData() && p.mediaType() == AVMediaType::AVMEDIA_TYPE_VIDEO)
            {
                if (!decoder)
                {
                    if (shared_ptr<Stream> stream = p.streamRef().lock())
                    {
                        decoder = make_unique<VideoDecoder>(*stream);
                    }
                    else
                    {
                        throw std::runtime_error("Demuxer not present");
                    }
                }

                FrameList frames = decoder->decodePacket(p);

                for (auto &fr : frames)
                {
                    if (!filter)
                    {
                        filter = make_unique<SimpleVideoFilter>("[in0][in1]hstack=inputs=2[out0]; [in2]null[out1]", fr);
                    }

                    FrameList filterFrames = filter->filterFrame(fr);

                    for (auto& fr : filterFrames)
                    {
                        count++;
                    }
                    //qDebug() << fr.timestampSeconds();
                }
            }
        }

        FrameList remainingFrames = decoder->drain();

        for (auto& fr : remainingFrames)
        {
            FrameList filterFrames = filter->filterFrame(fr);

            for (auto& fr : remainingFrames)
            {
                count++;
            }
            //qDebug() << fr.timestampSeconds();
        }

    }
    catch (const std::exception &e)
    {
        qDebug() << "exception: " << e.what();
    }

    double elapsed = (QDateTime::currentMSecsSinceEpoch() - startMs) / 1000.;
    qInfo() << "Finished " << count << " frames in " << elapsed << " FPS: " << count / elapsed;
}

void remuxingTest()
{
    int count = 0;
    int64_t startMs = QDateTime::currentMSecsSinceEpoch();

    unique_ptr<Demuxer> demuxer = make_unique<Demuxer>("D:\\1hourPAL.mp4");
    unique_ptr<Muxer> muxer = make_unique<Muxer>("D:\\1hourPAL-remux.mp4");

    muxer->copyStreams(demuxer->streams());

    while (!demuxer->isEOS())
    {
        Packet p = demuxer->nextPacket();

        if (p.hasData())
        {
            muxer->writePacket(p);
            count++;
        }
    }

    muxer->close();

    double elapsed = (QDateTime::currentMSecsSinceEpoch() - startMs) / 1000.;
    qInfo() << "Finished " << count << " frames in " << elapsed << " FPS: " << count / elapsed;
}

int main(int argc, char *argv[])
{
    remuxingTest();

    return 0;
}
