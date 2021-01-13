#include "inputreader.hpp"

namespace JACFFmpegLib
{
    InputReader::InputReader(string inputUri)
    {
        (void)inputUri;
    }

    const vector<shared_ptr<Stream>>& InputReader::streams()
    {
        //if (demuxer)
        {
            return demuxer->streams();
        }
    }
}
