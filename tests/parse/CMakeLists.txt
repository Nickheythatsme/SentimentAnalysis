set(EXEC_NAME parse)

set(SOURCES
    main.cpp
    test_parse.cpp test_parse.h
    ../support.cpp ../support.h
    )


# Make the executable
add_executable(${EXEC_NAME} ${SOURCES})

# Link the libraries to the executable
target_link_libraries(${EXEC_NAME}
    vectorize
    )

