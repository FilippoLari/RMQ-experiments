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