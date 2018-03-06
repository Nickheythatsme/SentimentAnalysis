set(EXEC_NAME parse)

set(SOURCES
    main.cpp
    )


# Make the executable
add_executable(${EXEC_NAME} ${SOURCES})

# Link the libraries to the executable
target_link_libraries(${EXEC_NAME}
    vectorize
    )

message("Location: ${CMAKE_CURRENT_SOURCE_DIR}/UTF/sample.txt")
add_test(parse_test_sample ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/UTF8/sample.txt)
add_test(parse_test_small ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/UTF8/small.txt)
add_test(parse_test_utf8 ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/UTF8/UTF8.txt)
