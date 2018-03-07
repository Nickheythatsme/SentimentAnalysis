set(EXEC_NAME window)

set(SOURCES
    main.cpp
    ../support.cpp ../support.h
    )



# Make the executable
add_executable(${EXEC_NAME} ${SOURCES})

# Link the libraries to the executable
target_link_libraries(${EXEC_NAME}
    vectorize
    )
