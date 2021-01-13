#ifndef INPUTREADER_HPP
#define INPUTREADER_HPP

#include "common.hpp"

#include "demuxer.hpp"
#include "videodecoder.hpp"

namespace JACFFmpegLib
{
    class InputReader
    {
    private:
        unique_ptr<Demuxer> demuxer;

    public:
        InputReader(string inputUri);
        const vector<shared_ptr<Stream>>& streams();
    };
}

#endif // INPUTREADER_HPP
