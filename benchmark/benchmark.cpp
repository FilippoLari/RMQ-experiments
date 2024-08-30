#include <iostream>
#include <chrono>
#include <vector>
#include <type_traits>
#include <fstream>
#include <map>

#include "benchmark.hpp"
#include "type_list.hpp"
#include "../competitors/eps_rmq_wrapper.hpp"

int main(int argc, char* argv[]) {
    
    using Algorithms = TypeList<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 64>,
                                eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 128>,
                                eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 256>>;

    std::vector<int64_t> data;
    std::map<size_t, std::vector<query_type>> queries;

    Benchmark<int64_t> benchmark(data, queries);

    ForEach<Algorithms, Benchmark<int64_t>>::apply(benchmark);

    //benchmark.save();

    return 0;
}