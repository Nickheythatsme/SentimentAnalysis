cmake_minimum_required(VERSION 3.5)

set(TARGET
    test_parse
    )

# Find required packages
find_package (Threads REQUIRED)

cxx_test(${TARGET} ${TARGET}.h)
target_link_libraries(
    ${TARGET}
    ${CMAKE_THREAD_LIBS_INIT}
    vectorize
    )

