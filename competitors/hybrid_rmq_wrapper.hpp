#pragma once

#include "FL-RMQ/include/hybrid_rmq.hpp"

template<typename K, typename Range, typename Pos,
 typename Floating = float, size_t Threshold = 10000, size_t Epsilon = 64>
class HBRMQWrapper : public hybrid_rmq<K, Range, Pos, Floating, Threshold, Epsilon> {

public:
    
    HBRMQWrapper(std::vector<K> data) : hybrid_rmq<K, Range, Pos, Floating, Threshold, Epsilon>(data) {}

    static constexpr std::string name() {
        return "HBRMQ_" + std::to_string(Epsilon);
    }

    inline double bpe() const {
        return double(this->size()) / double(this->data_count()); 
    }

    inline size_t segments() const {
        return this->segment_count();
    }
};