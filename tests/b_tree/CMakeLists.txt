set(EXEC_NAME b_tree)

set(SOURCES
    main.cpp
    ../text_package.cpp ../text_package.h
    )

# Make the executable
add_executable(${EXEC_NAME} ${SOURCES})

add_test(b_tree
        ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME}/${EXEC_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/../text_samples/samples/*.txt)

# Include the b_tree directory
include_directories(../../src/libs/new_b_tree)

# Link the libraries to the executable
target_link_libraries(
        ${EXEC_NAME}
        vectorize
        )
