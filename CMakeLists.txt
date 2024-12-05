cmake_minimum_required(VERSION 3.10)
project(rmq_experiments)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O3")

set(CMAKE_CXX_STANDARD 20)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if (COMPILER_SUPPORTS_MARCH_NATIVE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif ()

include_directories(competitors)

add_library(fl_rmq_lib INTERFACE)

target_include_directories(fl_rmq_lib INTERFACE include ${CMAKE_CURRENT_SOURCE_DIR}/competitors/FL-RMQ/sdsl-lite/include)

target_include_directories(fl_rmq_lib INTERFACE include ${CMAKE_CURRENT_SOURCE_DIR}/competitors/FL-RMQ/libsais)

target_include_directories(fl_rmq_lib INTERFACE include ${CMAKE_CURRENT_SOURCE_DIR}/competitors/FL-RMQ/bit_vector/include)

target_include_directories(fl_rmq_lib INTERFACE include ${CMAKE_CURRENT_SOURCE_DIR}/competitors/FL-RMQ/bit_vector/_deps/pasta_utils-src/include)

target_include_directories(fl_rmq_lib INTERFACE include ${CMAKE_CURRENT_SOURCE_DIR}/competitors/FL-RMQ/bit_vector/_deps/tlx-src)

add_library(ferrada_rmq_lib STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/competitors/rmq/RMQRMM64.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/competitors/rmq/includes/Basic_rmq.cpp
)
target_include_directories(ferrada_rmq_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/competitors/rmq/includes)

file(GLOB SUCCINCT_SOURCES ${CMAKE_SOURCE_DIR}/competitors/succinct/*.cpp)
add_library(succinct_rmq_lib STATIC ${SUCCINCT_SOURCES})
target_include_directories(succinct_rmq_lib PUBLIC ${CMAKE_SOURCE_DIR}/competitors/succinct)

file(GLOB SDSL_LITE_SOURCES ${CMAKE_SOURCE_DIR}/competitors/sdsl-lite/lib/*.cpp)
add_library(sdsl_lib STATIC ${SDSL_LITE_SOURCES})
target_include_directories(sdsl_lib PUBLIC ${CMAKE_SOURCE_DIR}/competitors/sdsl-lite/include/sdsl)

add_library(cxxopts INTERFACE)
target_include_directories(cxxopts INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lib/cxxopts/include)

add_subdirectory(benchmark)