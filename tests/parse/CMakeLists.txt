
set(SHORT_PARSE_SOURCES
    short_parse.cpp
    ../text_package.cpp ../text_package.h
    )

set(LONG_PARSE_SOURCES
    long_parse.cpp
    ../text_package.cpp ../text_package.h
    )

# Make the executable
add_executable(short_parse ${SHORT_PARSE_SOURCES})
add_executable(long_parse ${LONG_PARSE_SOURCES})

# Link the libraries to the executable
target_link_libraries(
    short_parse
    vectorize
    )

# Link the libraries to the executable
target_link_libraries(
    long_parse
    vectorize
    )

add_test(short_parse
        ${CMAKE_CURRENT_BINARY_DIR}/short_parse
        "${CMAKE_CURRENT_SOURCE_DIR}/../text_samples/*.txt")

add_test(long_parse
        ${CMAKE_CURRENT_BINARY_DIR}/long_parse
        "${CMAKE_CURRENT_SOURCE_DIR}/../text_samples/*.txt")


# Set properties for clang tidy
set_target_properties(
    short_parse PROPERTIES
    CXX_STANDARD 14
    COMPILE_FLAGS "${WARNING_FLAGS}"
    )

if (CLANG_TIDY_EXE)
    set_target_properties(
        short_parse PROPERTIES
        CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
        )
endif()

set_target_properties(
    long_parse PROPERTIES
    CXX_STANDARD 14
    COMPILE_FLAGS "${WARNING_FLAGS}"
    )

if (CLANG_TIDY_EXE)
    set_target_properties(
        long_parse PROPERTIES
        CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
        )
endif()
