#include <iostream>
#include <chrono>
#include <vector>
#include <type_traits>
#include <fstream>
#include <map>

#include "benchmark.hpp"
#include "type_list.hpp"
#include "../competitors/eps_rmq_wrapper.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {
    
    /*using Algorithms = TypeList<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 64>,
                                eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 128>,
                                eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 256>>;*/

    std::vector<int64_t> data = read_data<int64_t>("uniform_10M.bin");
    std::map<size_t, std::vector<query_type>> queries = read_and_group_queries(40000, "queries_uniform_10M.bin");

    Benchmark<int64_t> benchmark(data, queries);

    benchmark.template run<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 64>>();
    benchmark.template run<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 128>>();
    benchmark.template run<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 256>>();

    //ForEach<Algorithms, Benchmark<int64_t>>::apply(benchmark);

    std::ofstream c_output("build_time.csv");
    std::ofstream q_output("query_time.csv");

    benchmark.save(c_output, q_output);

    c_output.close();
    q_output.close();

    return 0;
}