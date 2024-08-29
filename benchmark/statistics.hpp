#pragma once

#include <fstream>
#include <string>

#include "benchmark.hpp"

struct construction_stats {
    static const std::string csv_header;

    std::string algorithm;
    double time;
    size_t space;
    double bpe;

    construction_stats(const std::string algorithm, const double time, const size_t space, const double bpe) : 
                        algorithm(algorithm), time(time), space(space), bpe(bpe) {}

};

const std::string construction_stats::csv_header = "algorithm,time,space,bpe";

struct queries_stats {
    static const std::string csv_header;

    std::string algorithm;
    size_t range;
    double time;

    queries_stats(const std::string algorithm, const size_t range, const double time) : algorithm(algorithm), range(range), time(time) {}
};

const std::string queries_stats::csv_header = "algorithm,range,time";

template<typename BenchmarkType>
void print_construction_stats(const std::vector<BenchmarkType> &benchmarks, const std::ofstream &output) {

    output << construction_stats::csv_header << std::endl;

    for(const auto &benchmark : benchmarks) {
        construction_stats c_stats = benchmark.get_construction_stats();
        output << c_stats.algorithm << "," << c_stats.time << "," << c_stats.space << "," <<  c_stats.bpe << std::endl;
    }
}

template<typename BenchmarkType>
void print_queries_stats(const std::vector<BenchmarkType> &benchmarks, const std::ofstream &output) {
    
    output << queries_stats::csv_header << std::endl;

    for(const auto &benchmark : benchmarks) {
        for(const auto &q_stats : benchmark.get_queries_stats()) {
            output << q_stats.algorithm << "," << q_stats.range << "," <<  q_stats.time << std::endl;
        } 
    }
}