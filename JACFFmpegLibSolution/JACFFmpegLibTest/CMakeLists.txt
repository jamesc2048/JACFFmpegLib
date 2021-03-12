# CMakeList.txt : CMake project for JACFFmpegLib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)
project("JACFFmpegLibTest")

add_executable(JACFFmpegLibTest "main.cpp" "doctest.h")
set_property(TARGET JACFFmpegLibTest PROPERTY CXX_STANDARD 20)

#target_precompile_headers(JACFFmpegLib PUBLIC pch.hpp)
target_link_libraries(JACFFmpegLibTest PUBLIC JACFFmpegLib)
target_include_directories(JACFFmpegLibTest PUBLIC ../JACFFmpegLib)
