cmake_minimum_required(VERSION 3.15)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(VCPKG_VERBOSE ON)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
    message("Loaded VCPKG at $ENV{VCPKG_ROOT}")
endif()

project(JACFFmpegLib)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_SHARED_LIBS "Build shared lib" ON)

# libav libraries common path, check for one
find_path(LIBAV_INCLUDE_DIR libavformat/avformat.h)

find_library(LIBAV_AVFORMAT_LIB avformat)
find_library(LIBAV_AVCODEC_LIB avcodec)
find_library(LIBAV_AVFILTER_LIB avfilter)
find_library(LIBAV_AVUTIL_LIB avutil)
find_library(LIBAV_SWSCALE_LIB swscale)

set(LIBAV_LIBS ${LIBAV_AVFORMAT_LIB} ${LIBAV_AVCODEC_LIB} ${LIBAV_AVFILTER_LIB} ${LIBAV_AVUTIL_LIB} ${LIBAV_SWSCALE_LIB})

message("LibAV Include dir: ${LIBAV_INCLUDE_DIR}")
message("LibAV libs: ${LIBAV_LIBS}")

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.hpp)

message(${SOURCES} ${HEADERS})

add_library(JACFFmpegLib ${SOURCES} ${HEADERS})

include_directories(${LIBAV_INCLUDE_DIR})
target_link_libraries(JACFFmpegLib ${LIBAV_LIBS})