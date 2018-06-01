cmake_minimum_required(VERSION 3.5)

message("Including tests")
enable_testing()
add_subdirectory(parse)
add_subdirectory(b_tree)
add_subdirectory(queue)
