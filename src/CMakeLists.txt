cmake_minimum_required(VERSION 3.5)

# Communicate that this CMakeLists file has been included
message("Including vectorize")

# Define the library name
set(LIBRARY_NAME vectorize)

# Define the sources to be added to the library
set(SOURCES
    parse.cpp parse.h
    utf8_manip.cpp utf8_manip.h
    text_package.h text_package.cpp
	btree.hpp
    )

# Create the library
add_library(${LIBRARY_NAME} STATIC ${SOURCES})

# Add clang-tidy if it's found
set_target_properties(
    ${LIBRARY_NAME} PROPERTIES
    CXX_STANDARD 14
    COMPILE_FLAGS "${WARNING_FLAGS}"
    )

if (CLANG_TIDY_EXE)
    set_target_properties(
        ${LIBRARY_NAME} PROPERTIES
        CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
        )
endif()

# Make sure the compiler can find include files for the library
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
