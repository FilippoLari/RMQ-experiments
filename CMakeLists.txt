cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MyProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the directories containing header files
include_directories(utils)

# Add subdirectories (assuming each submodule in 'competitors' has its own CMakeLists.txt)
add_subdirectory(competitors)

# Define the source files for benchmark
set(BENCHMARK_SOURCES
    benchmark/main.cpp
    # Add other source files from benchmark folder here
)

# Define the source files for experiments
set(EXPERIMENTS_SOURCES
    experiments/main.cpp
    # Add other source files from experiments folder here
)

# Add the executables
add_executable(benchmark ${BENCHMARK_SOURCES})
add_executable(experiments ${EXPERIMENTS_SOURCES})

# Link libraries from competitors if needed (example assuming a competitor library is generated)
# target_link_libraries(benchmark PRIVATE competitor_lib)
# target_link_libraries(experiments PRIVATE competitor_lib)

# Set the output directory for executables
set_target_properties(benchmark experiments
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
)