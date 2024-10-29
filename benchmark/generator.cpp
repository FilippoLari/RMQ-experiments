#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <cassert>

#include "generator.hpp"

int main(int argc, char* argv[]) {

    //const size_t n = 1000000000;
    //const size_t q = 10000;

    const size_t n = 2210395553;
    const size_t q = 10000;

    //std::vector<int64_t> uniform_values = generate_uniform<int64_t>(100000000, 1, 1000000000);

    //std::vector<int64_t> uniform_values = generate_uniform<int64_t>(n, 1, 10000000000);

    //write_data<int64_t>(uniform_values, "uniform_1B.bin");

    std::vector<size_t> ranges = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

    std::vector<query_type> queries = generate_queries(n, q, ranges);

    //write_data<query_type>(queries, "queries_uniform_1B.bin");

    write_data<query_type>(queries, "queries_english.bin");

    return 0;
}