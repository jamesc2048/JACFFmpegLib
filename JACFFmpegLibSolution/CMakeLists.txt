# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.16)

project (JACFFmpegLibSolution)

if (WIN32)
	set(FFMPEG_DEV_ROOT ../../FFmpegLibs)
endif()

# Include sub-projects.
add_subdirectory ("JACFFmpegLib")
add_subdirectory ("JACFFmpegLibTest")
