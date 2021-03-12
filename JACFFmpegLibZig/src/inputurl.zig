const std = @import("std");
const testing = std.testing;

const InputURLError = error {
    DemuxerError,
    CodecError
};

const InputURL = struct {
    const Self = @This();
    
    url: []const u8,

    fn init(self: Self) !InputURL {
        return self;
    }

    fn deinit(self: Self) void {

    }
};

test "InputURL" {
    const input = InputURL {
        .url = "wow"
    };

    defer input.deinit();

    testing.expectEqualStrings(input.url, "wow");
}