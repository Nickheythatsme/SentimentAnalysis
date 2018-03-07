set(EXEC_NAME window)

set(SOURCES
    main.cpp
    support.cpp support.h
    )


# Make the executable
add_executable(${EXEC_NAME} ${SOURCES})

# Link the libraries to the executable
target_link_libraries(${EXEC_NAME}
    vectorize
    )

message("Location: ${CMAKE_CURRENT_SOURCE_DIR}/UTF/sample.txt")
add_test(window_test_comment ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/UTF8/comment.txt)
add_test(window_test_sample ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/UTF8/sample.txt)
