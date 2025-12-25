cmake_minimum_required(VERSION 3.30)
project(TaskProcessor)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wcast-qual -O3)
endif()

add_executable(TaskProcessor main.cpp)
include_directories(includes)
