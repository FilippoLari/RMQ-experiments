#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <map>

#include "statistics.hpp"

using query_type = std::pair<size_t, size_t>;

using timer = std::chrono::high_resolution_clock;

template<class T>
void do_not_optimize(T const &value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

template<typename T, typename BuildTimeFormat = std::chrono::seconds,
         typename QueriesTimeFormat = std::chrono::nanoseconds>
class Benchmark {

    std::vector<T> data;

    // queries are grouped by range size
    std::map<size_t, std::vector<query_type>> queries;

    // maps algorithms names to construction statistics
    std::map<std::string, construction_stats> c_stats_map;

    // maps ranges to queries statistics
    // notice we have a statistic per query range
    std::map<size_t, std::vector<queries_stats>> q_stats_map;

public:

    explicit Benchmark(std::vector<T> &data, std::map<size_t, std::vector<query_type>> &queries) : data(data), queries(queries) {}

    template<class RMQ>
    void operator()() {
        auto start = timer::now();

        RMQ rmq = RMQ(data);

        const double time = std::chrono::time_cast<BuildTimeFormat>(timer::now() - start).count(); 

        do_not_optimize(rmq);

        construction_stats c_stats = construction_stats(rmq.name(), time, rmq.size(), rmq.bpe());

        // assumes names are unique
        c_stats_map[rmq.name()] = c_stats;

        for(const auto &q : queries) {
            query_range(rmq, q.first, q.second);
        }
    }

    void save(const std::ofstream &c_output, const std::ofstream &q_output) const {
        c_output << construction_stats::csv_header << std::endl;

        for(const auto &entry : c_stats_map) {
            const std::string algorithm = entry.first;
            const construction_stats c_stats = entry.second;
            c_output << algorithm << "," << c_stats.time << "," << c_stats.space << "," <<  c_stats.bpe << std::endl;
        } 

        q_output << queries_stats::csv_header << std::endl;

        for(const auto &entry : q_stats_map) {
            const size_t range = entry.first;
            for(const auto &q_stats : entry.second)
                q_output << q_stats.algorithm << "," << range << "," <<  q_stats.time << std::endl;
        }
    }

private:

    template<class RMQ>
    void query_range(RMQ &rmq, const size_t range, const std::vector<query_type> queries) {
        size_t checksum = 0;

        auto f = [](query_type query, dependency) 
                    { return rmq.query(query.first, query.second) ^ dependency; };

        auto start = timer::now();

        for(const auto &query : queries) {
            checksum ^= f(query, checksum);
        }

        do_not_optimize(checksum);

        const double time = std::chrono::time_cast<QueriesTimeFormat>(timer::now() - start).count();

        q_stats_map[range].emplace_back((rmq.name(), time));
    }
};