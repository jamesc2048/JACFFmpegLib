const std = @import("std");
const testing = std.testing;

const c = @cImport({
    @cInclude("libavutil/avutil.h");
    @cInclude("libavformat/avformat.h");
    @cInclude("libavcodec/avcodec.h");
});

const InputUrlError = error {
    DemuxerError,
    CodecError
};

const InputUrl = struct {
    const Self = @This();
    
    url: []const u8,
    formatCtx: [*c]c.struct_AVFormatContext = null,
    codecCtx: [*c]c.struct_AVCodecContext = null,
    videoStreamIndex: ?i32 = null,
    bestVideoStream: [*c]c.struct_AVStream = null,
    bestAudioStream: [*c]c.struct_AVStream = null,

    fn init(self: Self) !void {
        var ret : c_int = c.avformat_open_input(null, @ptrCast([*c]const u8, &self.url), null, null);

        if (ret != 0) {
            return error.DemuxerError;
        }
    }

    fn deinit(self: Self) void {
        // close contexts
    }
};

test "InputUrl" {
    var input = InputUrl {
        .url = "wow"
    };

    try input.init();

    defer input.deinit();

    testing.expectEqualStrings(input.url, "wow");
}