#include <iostream>
#include <chrono>
#include <vector>
#include <type_traits>
#include <fstream>
#include <cmath>
#include <map>

#include "benchmark.hpp"
#include "cxxopts.hpp"
#include "utils.hpp"

#include "../competitors/fl_rmq_wrapper.hpp"
#include "../competitors/block_decomposition_wrapper.hpp"
#include "../competitors/segment_tree_wrapper.hpp"
#include "../competitors/sparse_table_wrapper.hpp"

#include "../competitors/fl_rmq_succ_wrapper.hpp"
#include "../competitors/ferrada_rmq_wrapper.hpp"
#include "../competitors/succinct_rmq_wrapper.hpp"
#include "../competitors/sdsl_rmq_wrapper.hpp"
#include "../competitors/hyperrmq_wrapper.hpp"

template<typename K>
void run_encoding_benchmark(Benchmark<K> &benchmark, const std::string &input_sequence, 
                            const std::string &output_build, const std::string &output_time) {
    // FL-RMQ
    if(input_sequence.find("pseudo") != std::string::npos) {
        benchmark.template run<SuccinctFLRMQWrapper<int64_t, int64_t, int64_t, float, 512, 0, 1024>>();
        benchmark.template run<SuccinctFLRMQWrapper<int64_t, int64_t, int64_t, float, 1024, 0, 2048>>();
        benchmark.template run<SuccinctFLRMQWrapper<int64_t, int64_t, int64_t, float, 2048, 0, 4096>>();
        benchmark.template run<SuccinctFLRMQWrapper<int64_t, int64_t, int64_t, float, 4096, 0, 8192>>();
    } else {
        benchmark.template run<SuccinctFLRMQWrapper<int64_t, int64_t, int64_t, float, 512, 1024, 1024>>();
        benchmark.template run<SuccinctFLRMQWrapper<int64_t, int64_t, int64_t, float, 1024, 2048, 2048>>();
        benchmark.template run<SuccinctFLRMQWrapper<int64_t, int64_t, int64_t, float, 2048, 4096, 4096>>();
        benchmark.template run<SuccinctFLRMQWrapper<int64_t, int64_t, int64_t, float, 4096, 8192, 8192>>();
    }

    benchmark.template run<FerradaRMQWrapper<int64_t>>();
    benchmark.template run<SuccinctRMQWrapper<int64_t>>();

    benchmark.template run<SdslRMQWrapper<int64_t, 1024, 128, 0>>();
    benchmark.template run<SdslRMQWrapper<int64_t, 2048, 128, 0>>();
    benchmark.template run<SdslRMQWrapper<int64_t, 4096, 128, 0>>();

    benchmark.template run<HyperRMQWrapper<64>>();
    benchmark.template run<HyperRMQWrapper<128>>();
    benchmark.template run<HyperRMQWrapper<256>>();
    benchmark.template run<HyperRMQWrapper<512>>();

    std::ofstream c_output(output_build);
    std::ofstream q_output(output_time);

    benchmark.save(c_output, q_output);

    c_output.close();
    q_output.close();
}

template<typename K>
void run_indexing_benchmark(Benchmark<K> &benchmark, const std::string &input_sequence, 
                            const std::string &output_build, const std::string &output_time) {
    // FL-RMQ
    if(input_sequence.find("pseudo") != std::string::npos) {
        benchmark.template run<FLRMQWrapper<int64_t, int64_t, int64_t, float, 0, 256>>();
        benchmark.template run<FLRMQWrapper<int64_t, int64_t, int64_t, float, 0, 512>>();
        benchmark.template run<FLRMQWrapper<int64_t, int64_t, int64_t, float, 0, 1024>>();
        benchmark.template run<FLRMQWrapper<int64_t, int64_t, int64_t, float, 0, 2048>>();
    } else {
        benchmark.template run<FLRMQWrapper<int64_t, int64_t, int64_t, float, 512, 1024>>();
        benchmark.template run<FLRMQWrapper<int64_t, int64_t, int64_t, float, 1024, 2048>>();
        benchmark.template run<FLRMQWrapper<int64_t, int64_t, int64_t, float, 2048, 4096>>();
        benchmark.template run<FLRMQWrapper<int64_t, int64_t, int64_t, float, 4096, 8192>>();
    }

    // sparse table
    benchmark.template run<SparseTableWrapper<int64_t>>();

    // block decomposition & segment tree
    if(input_sequence.find("english") != std::string::npos) {
        benchmark.template run<BlockDecompositionWrapper<int64_t, int64_t, 31>>(); // logn
        benchmark.template run<BlockDecompositionWrapper<int64_t, int64_t, 216>>(); // n^(1/4)
        benchmark.template run<BlockDecompositionWrapper<int64_t, int64_t, 1302>>(); // n^(1/3)
        benchmark.template run<BlockDecompositionWrapper<int64_t, int64_t, 47014>>(); // sqrt(n)

        benchmark.template run<SegmentTreeWrapper<int64_t, int64_t>>();
    } else {
        benchmark.template run<BlockDecompositionWrapper<int64_t, int32_t, 29>>(); // logn
        benchmark.template run<BlockDecompositionWrapper<int64_t, int32_t, 177>>(); // n^(1/4)
        benchmark.template run<BlockDecompositionWrapper<int64_t, int32_t, 1000>>(); // n^(1/3)
        benchmark.template run<BlockDecompositionWrapper<int64_t, int32_t, 31622>>(); // sqrt(n)

        benchmark.template run<SegmentTreeWrapper<int64_t, int32_t>>();
    }

    std::ofstream c_output(output_build);
    std::ofstream q_output(output_time);

    benchmark.save(c_output, q_output);

    c_output.close();
    q_output.close();
}

int main(int argc, char* argv[]) {
    
    cxxopts::Options options("Benchmark", "Benchmarking program for various RMQ implementations");

    options.add_options()
        ("i,indexing", "Run the benchmark using the indexing data structures, if not provided uses the encodings",
             cxxopts::value<bool>()->default_value("false"))
        ("s,sequence", "Path to the input sequence", cxxopts::value<std::string>())
        ("q,queries", "Path to the queries sequence", cxxopts::value<std::string>())
        ("n,num_queries", "Number of queries", cxxopts::value<int>())
        ("b,build", "Where to write the building statistics", cxxopts::value<std::string>())
        ("t,time", "Where to write the queries statistics", cxxopts::value<std::string>())
        ("h,help", "Print usage instructions");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    const bool indexing = result["indexing"].as<bool>();
    
    const std::string input_sequence = result["sequence"].as<std::string>();
    const std::string input_queries = result["queries"].as<std::string>();

    const int num_queries = result["num_queries"].as<int>();

    const std::string output_build = result["build"].as<std::string>();
    const std::string output_time = result["time"].as<std::string>();

    std::vector<int64_t> data = read_data<int64_t>(input_sequence);
    std::map<size_t, std::vector<query_type>> queries = read_and_group_queries(num_queries, input_queries);

    Benchmark<int64_t> benchmark(data, queries);

    if(indexing)
        run_indexing_benchmark(benchmark, input_sequence, output_build, output_time);
    else
        run_encoding_benchmark(benchmark, input_sequence, output_build, output_time);

    return 0;
}