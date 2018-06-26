cmake_minimum_required(VERSION 3.5)

enable_testing()
set(TARGET
    test_parse
    )

# Find required packages
find_package (Threads REQUIRED)

cxx_test("short_parse" ${TARGET})
target_link_libraries(
    "short_parse"
    ${CMAKE_THREAD_LIBS_INIT}
    vectorize
    )

add_test("short_parse" "${CMAKE_CURRENT_BINARY_DIR}/short_parse")
