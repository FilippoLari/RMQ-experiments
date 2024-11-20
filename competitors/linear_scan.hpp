#pragma once

#include <limits>
#include <cstdlib>
#include <climits>
#include <numeric>
#include <vector>

template<typename K, typename Pos>
class LinearScan {
    static_assert(std::is_integral_v<K>);
    static_assert(std::is_integral_v<Pos>);

    std::vector<K> data;

    size_t n;

public:

    LinearScan() = default;

    explicit LinearScan(const std::vector<K> &data) : data(data), n(data.size()) {}

    /**
     * Returns the position of the minimum inside the interval [i,j]
     * 
     * @param i the left extreme of the interval
     * @param j the right extreme of the interval
     * @return the position of the minimum inside [i,j] 
     */
    Pos query(size_t i, size_t j) const {
        
        K min = data[i];
        auto idx = i;

        for(auto k=i; k<=j; ++k)
            if(min > data[k]) [[unlikely]] {
                min = data[k];
                idx = k;
            }
        
        return idx;
    }

    inline size_t data_count() const {
        return n;
    }

    /**
     * Returns the size in bit of the data structure
     * @return the size in bit of the data structure
     */
    inline size_t size() const {
        return 0;
    }

    static constexpr std::string name() {
        return "LinearScan";
    }

    inline double bpe() const {
        return double(size()) / double(n); 
    }
};