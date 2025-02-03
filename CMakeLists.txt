cmake_minimum_required(VERSION 3.12)
project(MediaPlayer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(ffmpeg_libs_DIR /usr/lib/ffmpeg5.1.6)
set(ffmpeg_headers_DIR /usr/include/ffmpeg5.1.6)

include_directories(${ffmpeg_headers_DIR})
link_directories(${ffmpeg_libs_DIR})


find_package(Qt5 REQUIRED COMPONENTS Core Widgets Multimedia)
add_subdirectory(src/UI)
add_subdirectory(src/Media)