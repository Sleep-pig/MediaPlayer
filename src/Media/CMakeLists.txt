file(GLOB_RECURSE srcs CMAKE_CONFIGURE_DEPENDS include/*.hpp core/*.cpp)

add_library(media STATIC ${srcs})

target_include_directories(media PUBLIC include)

target_link_libraries(media  PRIVATE Qt5::Core Qt5::Widgets Qt5::Multimedia)
target_link_libraries(media PRIVATE 
avcodec avformat avutil swresample swscale
)