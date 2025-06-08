cmake_minimum_required(VERSION 3.12)
project(easyVGL C)

set(CMAKE_C_STANDARD 11)

set(PROJ_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Check for options that make sure the project is built correctly
include(check_options.cmake)

include(porting/CMakeLists.txt)

add_subdirectory(src)

add_subdirectory(examples)
