add_executable(generator generator.cpp)
target_link_libraries(generator cxxopts)

add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark cxxopts fl_rmq_lib ferrada_rmq_lib succinct_rmq_lib sdsl_lib)