file(GLOB_RECURSE srcs CMAKE_CONFIGURE_DEPENDS include/*.hpp core/*.cpp)

set(ffmpeg_libs_DIR /usr/lib/ffmpeg5.1.6)
set(ffmpeg_headers_DIR /usr/include/ffmpeg5.1.6)

include_directories(${ffmpeg_headers_DIR})
link_directories(${ffmpeg_libs_DIR})

add_library(media STATIC ${srcs})

target_include_directories(media PUBLIC include)

target_link_libraries(media  PRIVATE Qt5::Core Qt5::Widgets Qt5::Multimedia)
target_link_libraries(media PRIVATE 
avcodec avformat avutil swresample swscale
)