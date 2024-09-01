#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <cassert>

#include "utils.hpp"

template<typename T>
std::vector<int64_t> generate_uniform(const size_t n, const T lo, const T hi) {
    std::uniform_int_distribution<T> uniform_dis(lo, hi);
    std::vector<T> values;

    std::random_device rd;
    std::mt19937 gen(rd());

    for(size_t i = 0; i < n; ++i)
        values.push_back(uniform_dis(gen));

    return values;
}

std::vector<int64_t> generate_pseudo_increasing(const size_t n, const int64_t delta) {
    std::uniform_int_distribution<int64_t> uniform_dis(-delta, delta);
    std::vector<int64_t> values;

    std::random_device rd;
    std::mt19937 gen(rd());

    for(int64_t i = 0; i < n; ++i) {
        values.push_back(std::max<int64_t>(i+uniform_dis(gen), 0));
    } 

    return values;
}

std::vector<int64_t> generate_pseudo_decreasing(const size_t n, const int64_t delta) {
    std::uniform_int_distribution<int64_t> uniform_dis(-delta, delta);
    std::vector<int64_t> values;

    std::random_device rd;
    std::mt19937 gen(rd());

    for(int64_t i = 0; i < n; ++i) {
        values.push_back(std::max<int64_t>(n-i+uniform_dis(gen), 0));
    } 

    return values;
}

std::vector<query_type> generate_queries(const size_t n, const size_t q,
                                         const std::vector<size_t> &ranges) {
    std::vector<query_type> queries;
    queries.reserve(q * ranges.size());

    std::random_device rd;
    std::mt19937 gen(rd());

    for(const size_t range : ranges) {
        std::uniform_int_distribution<size_t> uniform_dis(0, n - range);

        for(size_t i = 0; i < q; ++i) {
            const size_t start = uniform_dis(gen);
            const size_t end = start + range - 1;
            assert(end < n);
            queries.emplace_back(start, end);
        }
    }

    return queries;
}

int main(int argc, char* argv[]) {

    const size_t n = 1000000000;
    const size_t q = 10000;

    //std::vector<int64_t> uniform_values = generate_uniform<int64_t>(100000000, 1, 1000000000);

    std::vector<int64_t> uniform_values = generate_uniform<int64_t>(n, 1, 10000000000);

    write_data<int64_t>(uniform_values, "uniform_1B.bin");

    std::vector<size_t> ranges = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

    std::vector<query_type> queries = generate_queries(n, q, ranges);

    write_data<query_type>(queries, "queries_uniform_1B.bin");

    return 0;
}