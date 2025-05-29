cmake_minimum_required(VERSION 3.13)
project(OptimizationPass LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic -fno-rtti -stdlib=libc++")

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/../llvm/include)
link_directories(${CMAKE_SOURCE_DIR}/../llvm/lib)

add_subdirectory(lib)
