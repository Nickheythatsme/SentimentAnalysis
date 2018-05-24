cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required


project(Queue)

# Define the exec name
set(EXEC_NAME queue)

# Define the sources for the executable
set(SOURCES
        main.cpp
        )

add_executable(${EXEC_NAME} ${SOURCES})

# Find thread library
find_package (Threads REQUIRED)

# Link the libraries to the executable
target_link_libraries(
        ${EXEC_NAME}
        ${CMAKE_THREAD_LIBS_INIT}
)
