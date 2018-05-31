set(EXEC_NAME b_tree)

set(SOURCES
    main.cpp
    ../text_package.cpp ../text_package.h
    )

find_package (Threads)

# Make the executable
add_executable(${EXEC_NAME} ${SOURCES})

add_test(b_tree
        ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/../text_samples/samples/*.txt)

# Include the b_tree directory
include_directories(../../src/libs/new_b_tree)

# Link the libraries to the executable
target_link_libraries(
        ${EXEC_NAME}
        vectorize
        ${CMAKE_THREAD_LIBS_INIT}
        )

# Find clang-tidy
find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    )
if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found")
else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-clang-analyzer-alpha.*")
endif()

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

