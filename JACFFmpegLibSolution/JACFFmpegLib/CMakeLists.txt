# CMakeList.txt : CMake project for JACFFmpegLib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)
project(JACFFmpegLib)

# Default to static lib
option(BUILD_SHARED_LIBS "Build Shared instead of Static" OFF)

message("JACFFmpegLib Build Shared: ${BUILD_SHARED_LIBS}")

file(GLOB SOURCES CONFIG_REQUIRED *.cpp)
file(GLOB HEADERS CONFIG_REQUIRED *.hpp)

add_library(JACFFmpegLib ${SOURCES} ${HEADERS})

if (FFMPEG_DEV_ROOT)
	message("Adding custom lib path")
	target_include_directories(JACFFmpegLib PUBLIC ${FFMPEG_DEV_ROOT}/include)
	target_link_directories(JACFFmpegLib PUBLIC ${FFMPEG_DEV_ROOT}/lib)
endif()

target_link_libraries(JACFFmpegLib avutil avformat avcodec swscale)
#target_compile_definitions(JACFFmpegLib PRIVATE JACFFMPEGLIB_BUILD)
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

