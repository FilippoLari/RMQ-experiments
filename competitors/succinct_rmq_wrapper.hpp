#pragma once

#include <vector>

#include "../competitors/succinct/cartesian_tree.hpp"
#include "../competitors/succinct/mapper.hpp"

template<typename K>
class SuccinctRMQWrapper {

    succinct::cartesian_tree rmq;
    size_t n;

public:
    
    SuccinctRMQWrapper(std::vector<K> data) : rmq(data), n(data.size()) {}

    static constexpr std::string name() {
        return "SuccinctRMQ";
    }

    inline size_t query(const size_t i, const size_t j) {
        return rmq.rmq(i, j);
    }

    inline double bpe() {
        return double(succinct::mapper::size_of<succinct::cartesian_tree>(rmq) * CHAR_BIT) / double(n); 
    }

    inline size_t size() {
        return succinct::mapper::size_of<succinct::cartesian_tree>(rmq);
    }
};