
set(PARSE_SOURCES
    test_parse.cpp
    )

# Find required packages
find_package (Threads REQUIRED)
find_package(Boost COMPONENTS unit_test_framework)

# Make the executable
add_executable(parse ${PARSE_SOURCES})

# Link the libraries to the executable
target_link_libraries(
    parse
    ${CMAKE_THREAD_LIBS_INIT}
    vectorize
	Boost::unit_test_framework
    )

add_test(parse
        ${CMAKE_CURRENT_BINARY_DIR}/parse
        "${CMAKE_BINARY_DIR}/aclImdb/test/neg/*.txt"
        "${CMAKE_BINARY_DIR}/aclImdb/test/pos/*.txt")

# Set properties for clang tidy
set_target_properties(
    parse PROPERTIES
    CXX_STANDARD 14
    COMPILE_FLAGS "${WARNING_FLAGS}"
    )

if (CLANG_TIDY_EXE)
    set_target_properties(
        parse PROPERTIES
        CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
        )
endif()

