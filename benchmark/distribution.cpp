#include <iostream>
#include <chrono>
#include <vector>
#include <type_traits>
#include <fstream>
#include <map>

#include "type_list.hpp"
#include "../competitors/eps_rmq_wrapper.hpp"
#include "utils.hpp"
#include "generator.hpp"

int main(int argc, char* argv[]) {
    
    const size_t trials = 1000;
    const size_t n = 1000000;

    const size_t lo = 1;
    const size_t hi = 1000000000;

    std::cout << "eps,segments,estimate" << std::endl;

    for(auto trial = 0; trial < trials; ++trial) {
        std::vector<int64_t> data = generate_uniform<int64_t>(n, lo, hi);

        eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 64> ds64(data);

        std::cout << 64 << "," << ds64.segment_count() << "," << std::ceil(double(n) / double(64)) << std::endl;

        eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 128> ds128(data);

        std::cout << 128 << "," << ds128.segment_count() << "," << std::ceil(double(n) / double(128)) << std::endl;

        eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 256> ds256(data);

        std::cout << 256 << "," << ds256.segment_count() << "," << std::ceil(double(n) / double(256)) << std::endl;

        eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 512> ds512(data);

        std::cout << 512 << "," << ds512.segment_count() << "," << std::ceil(double(n) / double(512)) << std::endl;

        eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 1024> ds1024(data);

        std::cout << 1024 << "," << ds1024.segment_count() << "," << std::ceil(double(n) / double(1024)) << std::endl;

        eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 2048> ds2048(data);

        std::cout << 2048 << "," << ds2048.segment_count() << "," << std::ceil(double(n) / double(2048)) << std::endl;

        eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 4096> ds4096(data);

        std::cout << 4096 << "," << ds4096.segment_count() << "," << std::ceil(double(n) / double(4096)) << std::endl;

        eps_rmq_wrapper<int64_t, int64_t, int64_t, float, 8192> ds8192(data);

        std::cout << 8192 << "," << ds8192.segment_count() << "," << std::ceil(double(n) / double(8192)) << std::endl;
    }

    return 0;
}