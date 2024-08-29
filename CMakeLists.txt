cmake_minimum_required(VERSION 3.10)
project(rmq_experiments)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O3")

set(CMAKE_CXX_STANDARD 20)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if (COMPILER_SUPPORTS_MARCH_NATIVE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif ()

add_subdirectory(benchmark)

add_subdirectory(experiments)

add_subdirectory(competitors)

add_subdirectory(tests)