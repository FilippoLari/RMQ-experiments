#pragma once

#include "FL-RMQ/include/fl_rmq_succ.hpp"

template<typename K, typename Range, typename Pos,
 typename Floating = float, size_t Epsilon = 256>
class SuccinctFLRMQWrapper : public SuccinctFLRMQ<K, Range, Pos, Floating, Epsilon> {

public:
    
    size_t n;

    SuccinctFLRMQWrapper(std::vector<K> data) : SuccinctFLRMQ<K, Range, Pos, Floating, Epsilon>(data), n(data.size()) {}

    static constexpr std::string name() {
        return "SuccFLRMQ_" + std::to_string(Epsilon);
    }

    inline double bpe() const {
        return double(this->size()) / double(n); 
    }
};