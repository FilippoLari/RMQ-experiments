#pragma once

#include <vector>

#include "FL-RMQ/include/block_decomposition.hpp"

template<typename K, typename Pos, size_t BlockSize>
class BlockDecompositionWrapper : public BlockDecomposition<K, Pos, BlockSize> {

    std::vector<K> data;

public:
    
    BlockDecompositionWrapper(std::vector<K> data) : data(data), BlockDecomposition<K, Pos, BlockSize>(data) {}

    size_t query(const size_t i, const size_t j) const {
        return BlockDecomposition<K, Pos, BlockSize>::query(data, i, j);
    }

    static constexpr std::string name() {
        return "BlockDecomposition_" + std::to_string(BlockSize);
    }

    inline double bpe() const {
        return double(this->size()) / double(data.size()); 
    }
};