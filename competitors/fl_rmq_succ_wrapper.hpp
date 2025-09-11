#pragma once

#include "FL-RMQ/include/fl_rmq_encoding.hpp"

template<typename K, typename Range, typename Pos,
 typename Floating = float, size_t Epsilon = 4096,
 size_t ExcSamples = 2048, size_t DataSamples = 0>
class SuccinctFLRMQWrapper : public EncodingFLRMQ<K, Range, Pos, Floating, Epsilon, ExcSamples, DataSamples> {

    size_t n;

public:
    
    SuccinctFLRMQWrapper(const std::vector<K> &data) : n(data.size()), EncodingFLRMQ<K, Range, Pos, Floating, Epsilon, ExcSamples, DataSamples>(data) {}

    inline size_t query(const size_t i, const size_t j) const {
        return EncodingFLRMQ<K, Range, Pos, Floating, Epsilon, ExcSamples, DataSamples>::query(i, j);
    }

    static constexpr std::string name() {
        return "SuccFLRMQ_" + std::to_string(Epsilon);
    }

    inline double bpe() const {
        return double(this->size()) / double(n); 
    }
};