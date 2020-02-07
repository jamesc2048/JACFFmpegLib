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
        unique_ptr<SimpleFilter> filter;

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
                        filter = make_unique<SimpleFilter>("format=bgr24,fps=25*5", fr);
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

int main(int argc, char *argv[])
{
    videoDecodeBenchmark();

    return 0;
}
