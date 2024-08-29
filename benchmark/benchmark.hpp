#include <string>
#include <vector>
#include <chrono>

#include "statistics.hpp"

using timer = std::chrono::high_resolution_clock;

template<class T>
void do_not_optimize(T const &value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

template<class RMQ, typename T>
class Benchmark {

    std::string algorithm;

    construction_stats c_stats;
    std::vector<queries_stats> q_stats;

    RMQ rmq;

    using query_type = std::pair<size_t, size_t>;

public:

    explicit Benchmark(const std::string &algorithm) : algorithm(algorithm){}

    template<typename Format = std::chrono::seconds>
    void benchmark_construction(const std::vector<T> &data) const {
        size_t checksum = 0;

        auto start = timer::now();

        rmq = RMQ(data);

        auto end =  timer::now();

        do_not_optimize(rmq);

        const double time = std::chrono::time_cast<Format>(stop - start).count() / double(runs); 

        c_stats(algorithm, time, rmq.size(), rmq.bpe());
    }

    template<typename Format = std::chrono::nanoseconds>
    void benchmark_queries(const std::vector<query_type> &queries) const {

        const size_t range = queries[0].second - queries[0].first + 1;

        size_t checksum = 0;

        // introduces a dependency between subsequent calls to avoid
        // the compiler to interleave their code
        auto f = [](query_type query, dependency) 
                    { return rmq.query(query.first, query.second) ^ dependency; };

        auto start = timer::now();

        for(const auto &query : queries) {
            checksum ^= f(query, checksum);
        }

        auto end =  timer::now();

        do_not_optimize(checksum);

        const double time = std::chrono::time_cast<Format>(stop - start).count() / double(queries.size()); 

        q_stats.emplace_back(algorithm, range, time);
    }

    construction_stats get_construction_stats() const {
        return c_stats;
    }

    std::vector<queries_stats> get_queries_stats() const {
        return q_stats;
    }

    /**
     * Intended usage:
     * 
     * eps = Benchmark<eps_rmq<..>>("eps_rmq_64");
     * 
     * ferrada = ..
     * 
     * gog = ..
     * 
     * const auto benchmarks = {eps_rmq, ferrada, gog};
     * 
     * for(const auto &benchmark : benchmarks)
     * {
     *  benchmark.benchmark_construction(data);
     *  
     *  for(const auto &ranges : ranges)
     *      benchmark.benchmark_queries(queries[range]);
     * }
     * 
     * print_construction_stats(benchmarks, c_output);
     * 
     * print_queries_stats(benchmarks, q_output);
     */
};