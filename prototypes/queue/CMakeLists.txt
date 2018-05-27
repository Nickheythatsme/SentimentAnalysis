cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required


project(Queue)

# Define the exec name
set(EXEC_NAME queue)

# Set .h include files
set(H_SOURCES
        worker.hpp
        job.hpp
    )

# Define the sources for the executable
set(SOURCES
        main.cpp
        job.hpp
        worker.hpp
        )

add_executable(${EXEC_NAME} ${SOURCES} ${H_SOURCES})

# Find thread library
find_package(Threads REQUIRED)

# Link the libraries to the executable
target_link_libraries(
        ${EXEC_NAME}
        ${CMAKE_THREAD_LIBS_INIT}
        )
