set(EXEC_NAME parse)

set(SOURCES
    main.cpp
    )

# Make the executable
add_executable(${EXEC_NAME} ${SOURCES})

add_test(pase_regular
    ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME}/${EXEC_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/../text_samples/samples/*)

# Link the libraries to the executable
target_link_libraries(${EXEC_NAME}
    vectorize
    )
