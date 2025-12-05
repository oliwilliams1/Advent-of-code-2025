cmake_minimum_required(VERSION 3.15)

project(AdventOfCodeDay3 VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_executable(AdventOfCodeDay3 ${SOURCES})

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/data.txt" 
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")