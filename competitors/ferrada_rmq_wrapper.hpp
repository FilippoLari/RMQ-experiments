#pragma once

#include <vector>

#include "../competitors/rmq/includes/RMQRMM64.h"

template<typename K>
class FerradaRMQWrapper {

    RMQRMM64 rmq;
    size_t n;

public:
    
    FerradaRMQWrapper(std::vector<K> data) : rmq(data.data(), data.size()), n(data.size()) {}

    static constexpr std::string name() {
        return "FerradaRMQ";
    }

    inline size_t query(const size_t i, const size_t j) {
        return rmq.queryRMQ(i, j);
    }

    inline double bpe() {
        return double(rmq.getSize() * CHAR_BIT) / double(n);
    }

    inline size_t size() {
        return rmq.getSize();
    }
};