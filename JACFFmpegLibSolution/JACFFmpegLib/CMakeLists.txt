# CMakeList.txt : CMake project for JACFFmpegLib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

set(BUILD_SHARED_LIBS no)

add_library(JACFFmpegLib "JACFFmpegLib.hpp" "frame.hpp" "frame.cpp" "inputUrl.hpp" "inputUrl.cpp")
set_property(TARGET JACFFmpegLib PROPERTY CXX_STANDARD 17)

target_precompile_headers(JACFFmpegLib PUBLIC pch.hpp)

if(MSVC)
  target_compile_options(JACFFmpegLib PRIVATE /W4 /WX)
else()
  target_compile_options(JACFFmpegLib PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# TODO: Add tests and install targets if needed.
