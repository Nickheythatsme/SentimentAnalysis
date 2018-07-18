cmake_minimum_required(VERSION 3.5)

# Communicate that this CMakeLists file has been included
message("Including vectorize")

# Define the library name
set(LIBRARY_NAME vectorize)

# Define the sources to be added to the library
set(SOURCES
    parse.cpp parse.h
    text_package.h text_package.cpp
	btree.hpp holder.hpp
    )

# Create the library
add_library(${LIBRARY_NAME} STATIC ${SOURCES})

# Make sure the compiler can find include files for the library
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Find required packages
find_package (Threads REQUIRED)
add_executable (vectorizer vectorizer.cpp ${SOURCES})
target_link_libraries(
    vectorizer
    ${CMAKE_THREAD_LIBS_INIT}
    vectorize
    )

