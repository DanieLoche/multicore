cmake_minimum_required(VERSION 2.8)
project(multicoreScheduler)
file(GLOB files src/*.cpp)
set(HEADER_FILES headers)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


add_executable(multicoreScheduler ${files})
target_include_directories(multicoreScheduler PRIVATE ${HEADER_FILES})
