# CMakeList.txt : CMake project for TestProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.18)

# Add source to this project's executable.
add_library(JACFFmpegLib "inputURL.cpp" "inputURL.hpp")

# TODO: Add tests and install targets if needed.
