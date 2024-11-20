cmake_minimum_required(VERSION 3.10)
project(rmq_experiments)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O3")

set(CMAKE_CXX_STANDARD 20)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if (COMPILER_SUPPORTS_MARCH_NATIVE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif ()

include_directories(${CMAKE_SOURCE_DIR}/competitors)

# add libsais
set(LIBSAIS_DIR ${CMAKE_SOURCE_DIR}/lib/libsais)
set(LIBSAIS_LIB ${LIBSAIS_DIR}/liblibsais.a)

add_library(libsais STATIC IMPORTED)
set_target_properties(libsais PROPERTIES IMPORTED_LOCATION ${LIBSAIS_LIB})

target_include_directories(libsais INTERFACE ${LIBSAIS_DIR}/include)

add_library(cxxopts INTERFACE)
target_include_directories(cxxopts INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lib/cxxopts/include)

add_subdirectory(benchmark)