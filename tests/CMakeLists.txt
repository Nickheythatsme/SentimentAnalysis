cmake_minimum_required(VERSION 3.5)

message("Including tests")
enable_testing()
add_subdirectory(parse)
add_subdirectory(long_parse)
add_subdirectory(window)

# Parse tests
set(EXEC_NAME parse)
add_test(parse_test_sample 
    ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME}/${EXEC_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/text_samples/all.txt)
add_test(parse_test_small 
    ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME}/${EXEC_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/text_samples/small.txt)

# Window tests
set(EXEC_NAME window)
add_test(window_test_comment 
    ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME}/${EXEC_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/text_samples/comment.txt)
add_test(window_test_sample 
    ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME}/${EXEC_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/text_samples/all.txt)

