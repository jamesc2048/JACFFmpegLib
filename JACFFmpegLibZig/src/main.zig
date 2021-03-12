const std = @import("std");
const testing = std.testing;

const c = @cImport({
    @cInclude("libavformat/avformat.h");
    @cInclude("libavcodec/avcodec.h");
});

const InputReader = struct
{
    const Self = @This();

    url: []const u8,
    formatCtx: [*c]c.struct_AVFormatContext = null,
    codecCtx: [*c]c.struct_AVCodecContext = null,
    videoStreamIndex: i32 = -1,
    videoStream: [*c]c.struct_AVStream = null,

    pub fn init(self: *Self) !void {   
        self.formatCtx = c.avformat_alloc_context();
        var ret = c.avformat_open_input(&self.formatCtx, "E:\\stitchInput.mp4", null, null);

        if (ret < 0) 
        {
            return error.OutOfMemory;    
        }

        ret = c.avformat_find_stream_info(self.formatCtx, null);

        if (ret < 0) 
        {
            return error.OutOfMemory;    
        }

        std.debug.warn("{}", .{ret});

        var decoder : [*c]c.struct_AVCodec = undefined;

        ret = c.av_find_best_stream(self.formatCtx, c.enum_AVMediaType.AVMEDIA_TYPE_VIDEO, -1, -1, &decoder, 0);

        if (ret < 0) 
        {
            return error.OutOfMemory;    
        }

        self.videoStreamIndex = ret;
        self.videoStream = self.formatCtx.*.streams[@intCast(usize, self.videoStreamIndex)];

        c.av_dump_format(self.formatCtx, 0, "aaaa", 0);

        return ret;
    }

    pub fn deinit(self: *Self) void {
        c.avformat_close_input(&self.formatCtx);
        c.avcodec_free_context(&self.codecCtx);
    }
};

test "open demuxer" {
    var d: InputReader = .{
         .url = "test"
    };

    const retval = d.init();

    defer d.deinit();

    testing.expectEqual(retval, 0);
}