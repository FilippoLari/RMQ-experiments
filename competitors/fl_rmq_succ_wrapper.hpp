#pragma once

#include "FL-RMQ/include/fl_rmq_succ.hpp"

template<typename K, typename Range, typename Pos,
 typename Floating = float, size_t ExcSamples = 2048,
 size_t DataSamples = 0, size_t Epsilon = 4096>
class SuccinctFLRMQWrapper : public SuccinctFLRMQ<K, Range, Pos, Floating, ExcSamples, DataSamples, Epsilon> {

    size_t n;

public:
    
    SuccinctFLRMQWrapper(const std::vector<K> &data) : n(data.size()), SuccinctFLRMQ<K, Range, Pos, Floating, ExcSamples, DataSamples, Epsilon>(data) {}

    inline size_t query(const size_t i, const size_t j) const {
        return SuccinctFLRMQ<K, Range, Pos, Floating, ExcSamples, DataSamples, Epsilon>::query(i, j);
    }

    static constexpr std::string name() {
        return "SuccFLRMQ_" + std::to_string(Epsilon);
    }

    inline double bpe() const {
        return double(this->size()) / double(n); 
    }
};