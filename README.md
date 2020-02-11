# JACFFmpegLib
FFmpeg C++ intermediate level wrapper. 

## Goals
The goal is to be lower level than for example https://github.com/twitter/vireo, but slightly higher level than making the FFmpeg calls directly. Frame-by-frame control is retained and as such you can easily buffer or modify the data in transit.
Sensible defaults should be applied whenever needed for essential operation, such as applting AV_CODEC_FLAG_GLOBAL_HEADER flag for approrpiate formats.

## Roadmap (roughly in order of interest)
- [X] Demuxer (opens FFmpeg compatible URI and outputs `Packet`s)
- [X] VideoDecoder (decodes video `Packet`s into `Frame`s) 
- [ ] VideoFormatConverter (converts Video `Frame`s resolution and/or formats)
- [X] 1 to 1 VideoFilter (AVFilter graph with single input and single output)
- [ ] Muxer (output to FFmpeg supported URI, accepts `Packet`s)
- [ ] VideoEncoder
- [ ] AudioEncoder
- [ ] Many to many Filter (AVFilter full support)
- [ ] AudioDecoder 
- [ ] AudioFormatConverter (converts Video `Frame`s resolution and/or formats)

## Maybe
- [ ] Python wrapper
- [ ] Generic Swig wrapper
