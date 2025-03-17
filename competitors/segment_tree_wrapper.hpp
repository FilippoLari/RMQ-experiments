#pragma once

#include <vector>

#include "FL-RMQ/include/segment_tree.hpp"

template<typename K, typename Pos>
class SegmentTreeWrapper : public SegmentTree<K, Pos> {

    std::vector<K> data;

public:
    
    SegmentTreeWrapper(std::vector<K> data) : data(data), SegmentTree<K, Pos>(data) {}

    size_t query(const size_t i, const size_t j) const {
        return SegmentTree<K, Pos>::query(i, j);
    }

    static constexpr std::string name() {
        return "SegmentTree";
    }

    inline double bpe() const {
        return double(this->size()) / double(data.size()); 
    }
};