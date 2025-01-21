file(GLOB_RECURSE srcs CMAKE_CONFIGURE_DEPENDS include/*.hpp core/*.cpp)

add_executable(MediaPlayer ${srcs})

target_include_directories(MediaPlayer PUBLIC include)
target_link_libraries(MediaPlayer  PRIVATE Qt5::Core Qt5::Widgets Qt5::Multimedia)
target_link_libraries(MediaPlayer  PRIVATE media)