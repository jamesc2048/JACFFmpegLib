# JACFFmpegLib
FFmpeg C++ intermediate level wrapper. 
Lower level than something like https://github.com/twitter/vireo, but slightly higher level than using FFmpeg directly.

## Goals
The goal is to make FFmpeg's full power accessible with a simpler, friendlier and more intuitive API.
As such you will get frame-by-frame control, and every operation invoked on the library will be routed directly to an FFmpeg call or field.
Some defaults are applied when they are needed to make basic functionality work (E.G. adding AV_CODEC_FLAG_GLOBAL_HEADER when MP4 container is used).
Also I want to enable easy manipulation of the intermediate results: So you will receive/send `Packet` and `Frame` classes which you can do whatever you like with: buffer them, modify them, etc. and then plug them into the next function until you are done.

## Build
On Windows, unzip FFmpeg install directory with bin, include, lib in FFmpeg_libs directory. Zeranoe prebuilt (https://ffmpeg.zeranoe.com/builds/) or custom built will work.

Dependencies for Debian/Ubuntu:
```sudo apt install qt5-qmake qt5-default libavformat-dev libavcodec-dev libavfilter-dev libavutil-dev libswscale-dev libswresample-dev```

Use `qmake` to build the project. On Windows you'll need to install the Qt SDK for this.
Or open the "JACFFmpegLibSolution.pro" project in Qt Creator.

## Planned features  (roughly in order)
- [X] Demuxer (open source from FFmpeg supported URI, shows Streams, outputs Packets)
- [ ] Muxer (output to FFmpeg supported URI, accepts Packets)
- [ ] VideoDecoder (decodes a Video stream to `Frame`s from `Packet`s)
- [ ] AudioDecoder (decodes an Audio stream to `Frame`s from `Packet`s)
- [ ] VideoFormatConverter (converts Video `Frame`s resolution and/or formats)
- [ ] AudioFormatConverter (converts Audio `Frame`s resolution and/or formats)
- [ ] VideoEncoder 
- [ ] AudioEncoder
- [ ] 1 to 1 Filter (AVFilter with single input and single output, config from string)
- [ ] Many to many Filter (AVFilter with multiple input and multiple output, config from string)
- [ ] Convenience classes which combine Demuxer/Decoders, Muxers/Encoders to quickly get `Frame`s in and out to sources and sinks
- [ ] Build which doesn't rely on Qt qmake
