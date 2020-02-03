#include <JACFFmpegLib.hpp>

using namespace JACFFmpegLib;

#include <string>
#include <QtCore>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    try
    {
        // Testing code
        unique_ptr<Demuxer> dem = make_unique<Demuxer>(R"(\\gb.evcam.com\private$\users\James.Crisafulli\Documents\1hourPAL.mp4)");

        int count = 0;

        vector<Packet> clones;

        unique_ptr<VideoDecoder> dec;

        while (!dem->isEOS())
        {
            Packet p = dem->nextPacket();

            if (p.hasData())
            {
                QString packetName;

                switch (p.getCodecType())
                {
                    case AVMediaType::AVMEDIA_TYPE_VIDEO:
                        packetName = "Video Packet";
                        break;

                    case AVMediaType::AVMEDIA_TYPE_AUDIO:
                        packetName = "Audio Packet";
                        break;

                    default:
                        packetName = "Unknown Packet";
                        break;
                }

                qDebug() << packetName  << p.getStreamIndex() << count;

                // if Demuxer object is still alive
                if (shared_ptr<Stream> ptr = p.getStreamRef().lock())
                {
                    if (p.getCodecType() == AVMediaType::AVMEDIA_TYPE_VIDEO)
                    {
                        qDebug() << ptr->width() << ptr->height() << ptr->codecTagString().c_str();

                        if (!dec)
                        {
                            dec = make_unique<VideoDecoder>(*ptr);
                        }
                    }
                    else if (p.getCodecType() == AVMediaType::AVMEDIA_TYPE_AUDIO)
                    {
                        qDebug() << ptr->codecTagString().c_str();
                    }
                }
                else
                {
                    qDebug() << "Stream ref is null";
                }

                if (p.getCodecType() == AVMediaType::AVMEDIA_TYPE_VIDEO && dec)
                {
                    FrameList frames = dec->decodePacket(p);
                    qDebug() << "Decoded " << frames.size() << " frames";

                    if (frames.size())
                    {
                        QFile f("D:\\out.yuv");
                        f.open(QIODevice::WriteOnly | QIODevice::Append);

                        vector<uint8_t> bytes = frames[0].dumpToBytes();
                        f.write((const char*)bytes.data(), bytes.size());
                    }
                }
            }
        }

        qDebug() << "Done";
    }
    catch (const std::exception &e)
    {
        qDebug() << "exception: " << e.what();
    }

    return 0;
}
