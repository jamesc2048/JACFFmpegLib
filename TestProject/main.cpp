#include <JACFFmpegLib.hpp>

using namespace JACFFmpegLib;

#include <string>
#include <QtCore>

int main(int argc, char *argv[])
{
    try
    {
        // Testing code
        Demuxer dem("D:\\1.mp4");

        int count = 0;

        vector<Packet> clones;

        while (!dem.isEOS())
        {
            Packet p = dem.nextPacket();

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

                qDebug() << packetName  << p.getStreamIndex() << count++;

                // if Demuxer object is still alive
                if (shared_ptr<Stream> ptr = p.getStreamRef().lock())
                {
                    if (p.getCodecType() == AVMediaType::AVMEDIA_TYPE_VIDEO)
                    {
                        qDebug() << ptr->width() << ptr->height() << ptr->codecTagString().c_str();
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
