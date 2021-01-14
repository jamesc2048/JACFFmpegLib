cmake_minimum_required (VERSION 3.18)

project(JACFFmpegLib)

set(CMAKE_CXX_STANDARD 17)

# Does not work for Static at the moment.
option(BUILD_SHARED_LIBS "Build Shared instead of Static" ON)

# libav libraries common path, check for one
find_path(LIBAV_INCLUDE_DIR libavformat/avformat.h)

find_library(LIBAV_AVFORMAT_LIB avformat)
find_library(LIBAV_AVCODEC_LIB avcodec)
find_library(LIBAV_AVUTIL_LIB avutil)

set(LIBAV_LIBS ${LIBAV_AVFORMAT_LIB} ${LIBAV_AVCODEC_LIB} ${LIBAV_AVUTIL_LIB})

message("Build Shared: ${BUILD_SHARED_LIBS}")
message("LibAV Include dir: ${LIBAV_INCLUDE_DIR}")
message("LibAV libs: ${LIBAV_LIBS}")

if(USING_VCPKG AND BUILD_SHARED_LIBS)
	# TODO how not to hardcode these? also these always point to the debug?
	find_file(LIBAV_AVFORMAT_DLL "bin/avformat-58.dll")
	find_file(LIBAV_AVCODEC_DLL "bin/avcodec-58.dll")
	find_file(LIBAV_AVUTIL_DLL "bin/avutil-56.dll")
	# why does VCPKG libavcodec link to swresample?
	find_file(LIBAV_SWRESAMPLE_DLL "bin/swresample-3.dll")
	find_file(X264_DLL "bin/libx264-157.dll")
	
	set(LIBAV_DLLS ${LIBAV_AVFORMAT_DLL} ${LIBAV_AVCODEC_DLL} ${LIBAV_AVUTIL_DLL} ${LIBAV_SWRESAMPLE_DLL} ${X264_DLL})
	message("LibAV dlls: ${LIBAV_DLLS}")
endif()

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.hpp)

message("Sources: ${SOURCES} ${HEADERS}")

add_library(JACFFmpegLib ${SOURCES} ${HEADERS})

target_include_directories(JACFFmpegLib PUBLIC ${LIBAV_INCLUDE_DIR})
target_link_libraries(JACFFmpegLib ${LIBAV_LIBS})
target_compile_definitions(JACFFmpegLib PRIVATE JACFFMPEGLIB_BUILD)

install(FILES ${LIBAV_DLLS} DESTINATION bin)
install(TARGETS JACFFmpegLib RUNTIME DESTINATION bin)
install(TARGETS JACFFmpegLib LIBRARY DESTINATION lib)
# TODO public headers?
install(FILES inputURL.hpp DESTINATION include)