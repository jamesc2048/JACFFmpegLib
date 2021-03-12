const Builder = @import("std").build.Builder;

pub fn build(b: *Builder) void {
    const mode = b.standardReleaseOptions();
    const lib = b.addStaticLibrary("JACFFmpegLibZig", "src/inputurl.zig");
    lib.linkLibC();
    lib.linkSystemLibrary("c");
    lib.linkSystemLibrary("avformat");
    lib.linkSystemLibrary("avcodec");
    lib.linkSystemLibrary("avutil");
    lib.addIncludeDir("/usr/include/x86_64-linux-gnu/");
    lib.addLibPath("/usr/lib/x86_64-linux-gnu/");
    //lib.addIncludeDir("../FFmpegStaticLibs/include");
    //lib.addLibPath("../FFmpegStaticLibs/lib");
    lib.setBuildMode(mode);
    lib.install();

    var main_tests = b.addTest("src/inputurl.zig");
    main_tests.setBuildMode(mode);
    main_tests.linkSystemLibrary("c");
    main_tests.linkSystemLibrary("avformat");
    main_tests.linkSystemLibrary("avcodec");
    main_tests.linkSystemLibrary("avutil");
    main_tests.addIncludeDir("/usr/include/x86_64-linux-gnu/");
    main_tests.addLibPath("/usr/lib/x86_64-linux-gnu/");
    //main_tests.addIncludeDir("../FFmpegStaticLibs/include");
    //main_tests.addLibPath("../FFmpegStaticLibs/lib");


    const test_step = b.step("test", "Run library tests");
    test_step.dependOn(&main_tests.step);
}
