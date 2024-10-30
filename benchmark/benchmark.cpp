#include <iostream>
#include <chrono>
#include <vector>
#include <type_traits>
#include <fstream>
#include <cmath>
#include <map>

#include "benchmark.hpp"
#include "type_list.hpp"
#include "cxxopts.hpp"
#include "utils.hpp"

#include "../competitors/eps_rmq_wrapper.hpp"
#include "../competitors/hybrid_rmq_wrapper.hpp"
#include "../competitors/sparse_table.hpp"
#include "../competitors/block_decomposition.hpp"

int main(int argc, char* argv[]) {
    
    cxxopts::Options options("Benchmark", "Benchmarking program for various RMQ implementations");

    options.add_options()
        ("s,sequence", "Path to the input sequence", cxxopts::value<std::string>())
        ("q,queries", "Path to the queries sequence", cxxopts::value<std::string>())
        ("n,num_queries", "Number of queries", cxxopts::value<int>())
        ("b,build", "Where to write the building statistics", cxxopts::value<std::string>())
        ("t,time", "Where to write the queries statistics", cxxopts::value<std::string>())
        ("h,help", "Print usage instructions");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << "\n";
        return 0;
    }

    const int num_queries = result["num_queries"].as<int>();
    const std::string input_sequence = result["sequence"].as<std::string>();
    const std::string input_queries = result["queries"].as<std::string>();
    const std::string output_build = result["build"].as<std::string>();
    const std::string output_time = result["time"].as<std::string>();

    std::vector<int64_t> data = read_data<int64_t>(input_sequence);
    std::map<size_t, std::vector<query_type>> queries = read_and_group_queries(num_queries, input_queries);

    Benchmark<int64_t> benchmark(data, queries);

    benchmark.template run<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 64>>();
    benchmark.template run<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 128>>();
    benchmark.template run<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 256>>();
    benchmark.template run<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 512>>();
    benchmark.template run<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 1024>>();
    benchmark.template run<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 2048>>();

    benchmark.template run<sparse_table<int64_t, int32_t>>();

    benchmark.template run<block_decomposition<int64_t, int32_t, 30>>(); // logn
    benchmark.template run<block_decomposition<int64_t, int32_t, 163>>(); // n^(1/4)
    benchmark.template run<block_decomposition<int64_t, int32_t, 1000>>(); // n^(1/3)
    benchmark.template run<block_decomposition<int64_t, int32_t, 31622>>(); // sqrt(n)

    benchmark.template run<hybrid_rmq_wrapper<int64_t, int64_t, int64_t, float, 10000, 32>>();
    benchmark.template run<hybrid_rmq_wrapper<int64_t, int64_t, int64_t, float, 10000, 64>>();

    std::ofstream c_output(output_build);
    std::ofstream q_output(output_time);

    benchmark.save(c_output, q_output);

    c_output.close();
    q_output.close();

    return 0;
}