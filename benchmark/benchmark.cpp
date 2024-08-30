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
    
    /*using Algorithms = TypeList<eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 64>,
                                eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 128>,
                                eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 256>>;*/

    std::vector<int64_t> data = {1, 4, 5, 6, 5 ,2 ,8, 10};
    std::map<size_t, std::vector<query_type>> queries;

    std::vector<query_type> queries_3 = {std::make_pair(0,2), std::make_pair(3,5), std::make_pair(5,7)};
    queries[3] = queries_3;

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