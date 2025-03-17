#pragma once

#include <vector>

#include "FL-RMQ/include/sparse_table.hpp"

template<class Container, typename K>
class SparseTableWrapper : public SparseTable<Container> {

    size_t n;

public:
    
    SparseTableWrapper(std::vector<K> data) : n(data.size()), SparseTable<Container>(&data) {}

    size_t query(const size_t i, const size_t j) const {
        return SparseTable<Container>::query(i, j);
    }

    static constexpr std::string name() {
        return "SparseTable";
    }

    inline double bpe() const {
        return double(this->size()) / double(n); 
    }
};