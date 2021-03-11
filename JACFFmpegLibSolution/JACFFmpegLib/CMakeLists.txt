# CMakeList.txt : CMake project for JACFFmpegLib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

option(BUILD_SHARED_LIBS "Build Shared instead of Static" OFF)

# libav libraries common path, check for one
#find_path(LIBAV_INCLUDE_DIR libavformat/avformat.h)

#find_library(LIBAV_AVFORMAT_LIB avformat)
#find_library(LIBAV_AVUTIL_LIB avutil)

set(FFMPEG_BASEDIR C:/SDK/FFmpeg/)

message("Build Shared: ${BUILD_SHARED_LIBS}")

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.hpp)

add_library(JACFFmpegLib ${SOURCES} ${HEADERS})

set(LIBAV_LIBS avformat avcodec avutil swscale)

target_include_directories(JACFFmpegLib PUBLIC ${FFMPEG_BASEDIR}/include)
target_link_directories(JACFFmpegLib PUBLIC ${FFMPEG_BASEDIR}/lib)
target_link_libraries(JACFFmpegLib ${LIBAV_LIBS})
target_compile_definitions(JACFFmpegLib PRIVATE JACFFMPEGLIB_BUILD)
set_property(TARGET JACFFmpegLib PROPERTY CXX_STANDARD 17)

target_precompile_headers(JACFFmpegLib PUBLIC pch.hpp)

# Warnings as errors
if(MSVC)
  target_compile_options(JACFFmpegLib PRIVATE /W4 /WX /permissive-)
else()
  target_compile_options(JACFFmpegLib PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS JACFFmpegLib RUNTIME DESTINATION bin)
install(TARGETS JACFFmpegLib LIBRARY DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)

