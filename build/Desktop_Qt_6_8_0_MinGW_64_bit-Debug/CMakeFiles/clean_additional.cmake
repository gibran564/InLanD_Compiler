# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\InLanD_Compiler_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\InLanD_Compiler_autogen.dir\\ParseCache.txt"
  "InLanD_Compiler_autogen"
  )
endif()
