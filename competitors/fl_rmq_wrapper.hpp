#pragma once

#include <vector>

#include "FL-RMQ/include/fl_rmq.hpp"

template<typename K, typename Range, typename Pos,
 typename Floating = float, size_t Samples = 0, size_t Epsilon = 64, bool Rightmost = true>
class FLRMQWrapper : public FLRMQ<K, Range, Pos, Floating, Samples, Epsilon, Rightmost> {

    std::vector<K> data;

public:
    
    FLRMQWrapper(std::vector<K> data) : data(data), FLRMQ<K, Range, Pos, Floating, Samples, Epsilon, Rightmost>(data) {}

    size_t query(const size_t i, const size_t j) const {
        return FLRMQ<K, Range, Pos, Floating, Samples, Epsilon, Rightmost>::query(data, i, j);
    }

    static constexpr std::string name() {
        return "FLRMQ_" + std::to_string(Epsilon);
    }

    inline double bpe() const {
        return double(this->size()) / double(this->data_count()); 
    }
};