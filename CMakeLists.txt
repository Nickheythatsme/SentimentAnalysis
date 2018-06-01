cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required

project(SentimentAnalysis)

# Find clang-tidy
find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    )
if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found")
else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=google-default-arguments,google-runtime-*,llvm-*,modernize-*")
    #set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=google-default-arguments,google-runtime-*,modernize-*")
endif()

# Add the libraries and files from src
add_subdirectory(src)

# Add the tests subdirectory to start compiling tests
add_subdirectory(tests)

# Define the sources for the executable
set(SOURCES
    main.cpp
    )

enable_testing()
