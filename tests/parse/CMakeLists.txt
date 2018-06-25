cmake_minimum_required(VERSION 3.5)

set(TARGET
    test_parse
    )

# Find required packages
find_package (Threads REQUIRED)

set(TARGET_H "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET}.h")
set(TARGET_CPP "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}.cpp")

# Making .cpp file from CXXTESTGEN
add_custom_command(
    OUTPUT ${TARGET_CPP}
    COMMAND ${CXXTESTGEN} --output ${TARGET_CPP} --runner=ErrorPrinter ${TARGET_H}
    DEPENDS ${TARGET_H}
    )

message("Making executable")
add_executable(${TARGET} ${TARGET_CPP})
set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS "-Wno-effc++")
target_link_libraries(
    ${TARGET}
    ${CMAKE_THREAD_LIBS_INIT}
    vectorize
    )

