cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required

project(Queue)

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


# Define the exec name
set(EXEC_NAME queue)

# Set .h include files
set(H_SOURCES
        worker.cpp
        job.cpp
        )

# Define the sources for the executable
set(SOURCES
        main.cpp
        job.cpp
        worker.cpp
        )

add_executable(${EXEC_NAME} ${SOURCES} ${H_SOURCES})

# Find thread library
find_package(Threads REQUIRED)

# Link the libraries to the executable
target_link_libraries(
        ${EXEC_NAME}
        ${CMAKE_THREAD_LIBS_INIT}
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
