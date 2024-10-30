#pragma once

#include "eps_rmq/include/compressed_eps_rmq.hpp"

template<typename K, typename Range, typename Pos,
 typename Floating = float, size_t Epsilon = 64>
class compr_eps_rmq_wrapper : public compr_eps_rmq<K, Range, Pos, Floating, Epsilon> {

public:
    
    compr_eps_rmq_wrapper(std::vector<K> data) : compressed_eps_rmq<K, Range, Pos, Floating, Epsilon>(data) {}

    static constexpr std::string name() {
        return "compr_eps_rmq_" + std::to_string(Epsilon);
    }

    inline double bpe() const {
        return double(this->size()) / double(this->data_count()); 
    }

    inline size_t segments() const {
        return this->segment_count();
    }
};