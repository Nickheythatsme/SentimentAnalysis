cmake_minimum_required(VERSION 3.5)
project(SentimentAnalysis)

set(CMAKE_CXX_STANDARD 14)
message(${CMAKE_BUILD_TYPE})

find_package(PythonLibs REQUIRED)
include_directories(
        ${PYTHON_INCLUDE_DIRS}
                    )

set(SOURCES
        main.cpp
        src/parse.cpp
        src/parse.h
        src/count_words.cpp
        src/count_words.h
        src/window.cpp
        src/window.h
        src/make_window.cpp
        src/make_window.h
        )

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
                )
