#pragma once

#include "FL-RMQ/include/fl_rmq_succ.hpp"

template<typename K, typename Range, typename Pos,
 typename Floating = float, size_t Epsilon = 256>
class SuccinctFLRMQWrapper : public SuccinctFLRMQ<K, Range, Pos, Floating, Epsilon> {

public:
    
    SuccinctFLRMQWrapper(std::vector<K> data) : SuccinctFLRMQ<K, Range, Pos, Floating, Epsilon>(data) {}

    static constexpr std::string name() {
        return "SuccFLRMQ_" + std::to_string(Epsilon);
    }

    inline double bpe() const {
        return double(this->size()) / double(this->data_count()); 
    }
};