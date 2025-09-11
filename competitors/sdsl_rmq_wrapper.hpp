#pragma once

#include <vector>
#include <climits>
#include <sstream>

#include "../competitors/FL-RMQ/sdsl-lite/include/sdsl/rmq_succinct_rec_new.hpp"

template<typename K, uint32_t t_st_block_size,
    uint32_t t_super_block_size, uint32_t... t_block_sizes>
class SdslRMQWrapper {

    sdsl::rmq_succinct_rec_new<true, t_st_block_size, t_super_block_size, t_block_sizes...> rmq;
    std::vector<K> data;
    size_t n;

public:
    
    SdslRMQWrapper(std::vector<K> &data) : data(data), n(data.size()) {
        rmq = sdsl::rmq_succinct_rec_new<true, t_st_block_size, t_super_block_size, t_block_sizes...>(&data);
    }

    static constexpr std::string name() {
        std::ostringstream oss;
        oss << "SdslRMQ_" << t_super_block_size;
        ((oss << "_" << t_block_sizes), ...);
        return oss.str();
    }

    inline size_t query(const size_t i, const size_t j) {
        return rmq(i, j);
    }

    inline double bpe() {
        return double(sdsl::size_in_bytes(rmq) * CHAR_BIT) / double(n);
    }

    inline size_t size() {
        return sdsl::size_in_bytes(rmq);
    }
};