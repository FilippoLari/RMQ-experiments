#include <iostream>
#include <chrono>
#include <vector>
#include <type_traits>
#include <fstream>
#include <cmath>
#include <map>

#include "benchmark.hpp"
#include "type_list.hpp"
#include "../competitors/eps_rmq_wrapper.hpp"
#include "../competitors/hybrid_rmq_wrapper.hpp"
#include "../competitors/sparse_table.hpp"
#include "../competitors/block_decomposition.hpp"
#include "../competitors/linear_scan.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {
    
    std::vector<int64_t> data = read_data<int64_t>("pseudo_inc_1B_0.bin");
    std::map<size_t, std::vector<query_type>> queries = read_and_group_queries(10000, "queries_pseudo_inc_1B_0.bin");

    Benchmark<int64_t> benchmark(data, queries);

    benchmark.template run<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 64>>();
    benchmark.template run<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 128>>();
    benchmark.template run<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 256>>();
    benchmark.template run<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 512>>();
    benchmark.template run<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 1024>>();
    benchmark.template run<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 2048>>();

    benchmark.template run<sparse_table<int64_t, int32_t>>();

    /*std::cout << static_cast<size_t>(ceil(log2(1000000000))) << std::endl;
    std::cout << static_cast<size_t>((log2(1000000000)*sqrt(log2(1000000000)))) << std::endl;
    std::cout << static_cast<size_t>(sqrt(1000000000)) << std::endl;
    std::cout << static_cast<size_t>(pow(1000000000, 0.25)) << std::endl;
    std::cout << static_cast<size_t>(pow(1000000000, 0.333)) << std::endl;*/

    benchmark.template run<block_decomposition<int64_t, int32_t, 30>>(); // logn
    benchmark.template run<block_decomposition<int64_t, int32_t, 163>>(); // n^(1/4)
    benchmark.template run<block_decomposition<int64_t, int32_t, 1000>>(); // n^(1/3)
    benchmark.template run<block_decomposition<int64_t, int32_t, 31622>>(); // sqrt(n)

    benchmark.template run<hybrid_rmq_wrapper<int64_t, int64_t, int64_t, float, 10000, 32>>();
    benchmark.template run<hybrid_rmq_wrapper<int64_t, int64_t, int64_t, float, 10000, 64>>();
    //benchmark.template run<hybrid_rmq_wrapper<int64_t, int64_t, int64_t, float, 10000, 512>>();

    std::ofstream c_output("build_time_pseudo_inc_0.csv");
    std::ofstream q_output("query_time_pseudo_inc_0.csv");

    benchmark.save(c_output, q_output);

    c_output.close();
    q_output.close();

    return 0;
}