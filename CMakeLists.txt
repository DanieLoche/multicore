cmake_minimum_required(VERSION 3.1)
project(multicoreScheduler)
set(CMAKE_CXX_STANDARD 11)
file(GLOB SRC src/*.cpp)

SET(HEADER_FILES include)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(multicoreScheduler ${SRC})
target_include_directories(multicoreScheduler PRIVATE ${HEADER_FILES})
