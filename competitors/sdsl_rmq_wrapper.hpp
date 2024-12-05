#pragma once

#include <vector>

#include "../competitors/sdsl-lite/include/sdsl/rmq_succinct_rec_new.hpp"

template<typename K, uint32_t t_st_block_size,
    uint32_t t_super_block_size, uint32_t... t_block_sizes>
class SdslRMQWrapper {

    sdsl::rmq_succinct_rec_new<true, t_st_block_size, t_super_block_size> rmq;
    size_t n;

public:
    
    SdslRMQWrapper(std::vector<K> data) : n(data.size()) {
        rmq = sdsl::rmq_succinct_rec_new<true, t_st_block_size, t_super_block_size>(&data);
    }

    static constexpr std::string name() {
        return "SdslRMQ_" + std::to_string(t_st_block_size) + "_" + std::to_string(t_super_block_size);
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