cmake_minimum_required(VERSION 3.13)
project(FrontendCompiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(lib)
add_subdirectory(test)
