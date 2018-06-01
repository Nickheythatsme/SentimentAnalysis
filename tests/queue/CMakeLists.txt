set(EXEC_NAME queue)

set(SOURCES
    main.cpp
    matrix.cpp matrix.h
    ../text_package.cpp ../text_package.h
    )

# Make the executable
add_executable(${EXEC_NAME} ${SOURCES})

add_test(parse_regular
        ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/../text_samples/samples/*.txt)


# Find thread library
find_package(Threads REQUIRED)

# Link the libraries to the executable
target_link_libraries(
        ${EXEC_NAME}
        ${CMAKE_THREAD_LIBS_INIT}
        vectorize
        )

set_target_properties(
    ${EXEC_NAME} PROPERTIES
    CXX_STANDARD 14
    COMPILE_FLAGS "${WARNING_FLAGS}"
    )

if (CLANG_TIDY_EXE)
    set_target_properties(
        ${EXEC_NAME} PROPERTIES
        CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
        )
endif()

