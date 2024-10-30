# CMakeLists.txt in the benchmark directory

# Collect all .cpp files in the benchmark directory
file(GLOB_RECURSE BENCHMARK_SOURCES "*.cpp")

# Add each .cpp file as an executable
foreach(src_file ${BENCHMARK_SOURCES})
    # Extract the base name (filename without extension)
    get_filename_component(base_name ${src_file} NAME_WE)
    
    # Create an executable target for each .cpp file
    add_executable(${base_name} ${src_file})
    
    target_link_libraries(${base_name} cxxopts)
endforeach()
