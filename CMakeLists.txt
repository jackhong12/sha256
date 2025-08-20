cmake_minimum_required(VERSION 3.10)
project(LibSHA256 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(tools)
