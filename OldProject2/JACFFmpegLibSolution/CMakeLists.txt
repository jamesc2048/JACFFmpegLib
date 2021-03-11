# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.18)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    set(VCPKG_VERBOSE ON)
    set(VCPKG_APPLOCAL_DEPS ON)
    set(USING_VCPKG ON)
    message("Loaded VCPKG at $ENV{VCPKG_ROOT}")
endif()

project(JACFFmpegLibSolution)

enable_testing()

# Include sub-projects.
add_subdirectory("JACFFmpegLib")
add_subdirectory("TestProject")
