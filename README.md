# JACFFmpegLib
FFmpeg C++ intermediate level wrapper with C interface. 

## Goals
The goal is to be lower level than for example https://github.com/twitter/vireo, but higher level than making the FFmpeg calls directly. 
Frame-by-frame control is retained and as such you can easily buffer or modify the data in transit, although there will
Sensible defaults should be applied whenever needed for essential operation, such as applying `AV_CODEC_FLAG_GLOBAL_HEADER` flag for appropriate formats.

## Roadmap (roughly in order of interest)
- [ ] InputURL - Reads from FFmpeg URL and outputs `AVFrame`s - libavcodec, libavformat
- [ ] OutputURL - Outputs to FFmpeg URL from `AVFrame`s - libavcodec, libavformat
- [ ] VideoFormatConverter (converts Video `Frame`s resolution and/or formats) - libswscale
- [ ] Event mode (callback when video/audio frame is received)
- [ ] AudioFormatConverter (converts Audio `Frame`s resolution and/or formats) - libswresample
- [ ] 1 to 1 VideoFilter (AVFilter graph with single input and single output) - libavfilter
- [ ] Muxer (output to FFmpeg supported URI, accepts `Packet`s)
- [ ] Many to many Filter (AVFilter full support)
