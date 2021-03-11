cmake_minimum_required (VERSION 3.18)

project (TestProject)

set(CMAKE_CXX_STANDARD 17)

add_executable (TestProject "testProject.cpp" "testProject.hpp")
target_include_directories(TestProject PUBLIC JACFFmpegLib)
target_link_libraries(TestProject JACFFmpegLib)

install(TARGETS TestProject RUNTIME DESTINATION bin)
