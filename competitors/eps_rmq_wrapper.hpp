#pragma once

#include "eps_rmq/include/eps_rmq.hpp"

template<typename K, typename Range, typename Pos,
 typename Floating = float, size_t Epsilon = 64>
class eps_rmq_wrapper : public eps_rmq<K, Range, Pos, Floating, Epsilon> {

public:
    
    eps_rmq_wrapper(std::vector<K> data) : eps_rmq<K, Range, Pos, Floating, Epsilon>(data) {}

    static constexpr std::string name() {
        return "eps_rmq_" + std::to_string(Epsilon);
    }

    inline double bpe() const {
        return double(this->size()) / double(this->data_count()); 
    }
};