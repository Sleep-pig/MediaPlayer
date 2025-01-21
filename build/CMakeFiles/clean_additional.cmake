# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "src/Media/CMakeFiles/media_autogen.dir/AutogenUsed.txt"
  "src/Media/CMakeFiles/media_autogen.dir/ParseCache.txt"
  "src/Media/media_autogen"
  "src/UI/CMakeFiles/MediaPlayer_autogen.dir/AutogenUsed.txt"
  "src/UI/CMakeFiles/MediaPlayer_autogen.dir/ParseCache.txt"
  "src/UI/MediaPlayer_autogen"
  )
endif()
