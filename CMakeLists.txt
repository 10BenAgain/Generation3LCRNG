cmake_minimum_required(VERSION 3.10)

project(Generation2LCRNG)

set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_NAME "bin")

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC_FILES ${PROJECT_SOURCE_DIR}/main.c)

file(GLOB SRC_FILES_IN_SRC ${PROJECT_SOURCE_DIR}/src/*.c)

set(ALL_SRC_FILES ${SRC_FILES} ${SRC_FILES_IN_SRC})

add_executable(${EXECUTABLE_NAME} ${ALL_SRC_FILES})

