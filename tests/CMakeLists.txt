cmake_minimum_required(VERSION 3.5)
message("Including tests")
enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cxxtest-4.3)
set(CXXTESTGEN "${CMAKE_CURRENT_SOURCE_DIR}/cxxtest-4.3/bin/./cxxtestgen")
include(${CMAKE_CURRENT_SOURCE_DIR}/cxxtest-4.3/build_tools/cmake/CxxTest.cmake)


add_subdirectory(parse)
#add_subdirectory(queue)
