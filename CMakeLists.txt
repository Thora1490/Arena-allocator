cmake_minimum_required(VERSION 3.10)
project(arena-allocator)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(test tests/test.cpp)
target_include_directories(test PRIVATE include)

add_executable(benchmark tests/benchmark.cpp)
target_include_directories(benchmark PRIVATE include)
