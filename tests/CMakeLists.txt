cmake_minimum_required(VERSION 3.5)

message("Including tests")
set(CXXTEST_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cxxtest-4.3)
include_directories(${CXXTEST_PATH})
set(CXXTESTGEN "${CMAKE_CURRENT_SOURCE_DIR}/cxxtest-4.3/bin/./cxxtestgen")
add_subdirectory(parse)
#add_subdirectory(queue)
