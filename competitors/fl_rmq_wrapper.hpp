#pragma once

#include <vector>

#include "FL-RMQ/include/fl_rmq.hpp"

template<typename K, typename Range, typename Pos,
 typename Floating = float, size_t Epsilon = 64>
class FLRMQWrapper : public FLRMQ<K, Range, Pos, Floating, Epsilon> {

    std::vector<K> data;

public:
    
    FLRMQWrapper(std::vector<K> data) : data(data), FLRMQ<K, Range, Pos, Floating, Epsilon>(data) {}

    size_t query(const size_t i, const size_t j) const {
        return FLRMQ<K, Range, Pos, Floating, Epsilon>::query(data, i, j);
    }

    static constexpr std::string name() {
        return "FLRMQ_" + std::to_string(Epsilon);
    }

    inline double bpe() const {
        return double(this->size()) / double(this->data_count()); 
    }

    inline size_t segments() const {
        return this->segment_count();
    }
};