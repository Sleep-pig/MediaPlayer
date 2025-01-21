cmake_minimum_required(VERSION 3.12)
project(MediaPlayer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Multimedia)
add_subdirectory(src/UI)
add_subdirectory(src/Media)