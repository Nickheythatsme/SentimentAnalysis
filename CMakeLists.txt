cmake_minimum_required(VERSION 3.9)
project(SentimentAnalysis)

set(CMAKE_CXX_STANDARD 14)

find_package(PythonLibs REQUIRED)
include_directories(
        ${PYTHON_INCLUDE_DIRS}
                    )

set(SOURCES main.cpp src/parse.cpp src/parse.h)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
                )
