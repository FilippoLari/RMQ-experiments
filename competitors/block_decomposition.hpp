#pragma once

#include <limits>
#include <cstdlib>
#include <climits>
#include <numeric>
#include <vector>

#pragma once

#include <limits>
#include <cstdlib>
#include <climits>
#include <numeric>
#include <vector>

template<typename K, typename Pos, size_t block_size>
class block_decomposition {
    static_assert(std::is_integral_v<K>);
    static_assert(std::is_integral_v<Pos>);

    std::vector<std::pair<K, Pos>> block_minima;
    std::vector<K> data;

    size_t n;

public:

    block_decomposition() = default;

    explicit block_decomposition(const std::vector<K> &data) : data(data), n(data.size()) {
        if(n == 0) [[unlikely]]
            return;

        const size_t blocks = (n + block_size - 1) / block_size;

        block_minima.reserve(blocks);

        for(auto i = 0; i < n; i += block_size) {
            K min_value = data[i];
            Pos min_pos = i; 

            for(auto j = 0; (j < block_size && i + j < n); ++j) {
                if(data[i + j] < min_value) {
                    min_value = data[i + j];
                    min_pos = i+j;
                } 
            }

            block_minima.emplace_back(min_value, min_pos);
        }
    }

    /**
     * Returns the position of the minimum inside the interval [i,j]
     * 
     * @param i the left extreme of the interval
     * @param j the right extreme of the interval
     * @return the position of the minimum inside [i,j] 
     */
    Pos query(size_t i, size_t j) const {
        if(i==j) [[unlikely]]
            return i;
        
        const auto first_block =  i / block_size;
        const auto last_block = j / block_size;

        auto min_value = data[i];
        auto min_pos = i;

        if(first_block == last_block) {
            for(auto k = i; k <= j; ++k) {
                if(data[k] < min_value) {
                    min_value = data[k];
                    min_pos = k;
                } 
            }
        } else {
            for(auto k = i; k <= (first_block + 1) * block_size - 1; ++k) {
                if(data[k] < min_value) {
                    min_value = data[k];
                    min_pos = k;
                }
            }

            for(auto k = first_block + 1; k < last_block; ++k) {
                if(block_minima[k].first < min_value) {
                    min_value = block_minima[k].first;
                    min_pos = block_minima[k].second;
                }
            }

            for(auto k = last_block * block_size; k <= j; ++k) {
                if(data[k] < min_value) {
                    min_value = data[k];
                    min_pos = k;
                }
            }
        }

        return min_pos;
    }

    inline size_t data_count() const {
        return n;
    }

    inline size_t size() const {
        return ((block_minima.size() * sizeof(std::pair<K,Pos>)) 
                    + sizeof(n)) * CHAR_BIT;
    }

    static constexpr std::string name() {
        return "block_decomposition_" + std::to_string(block_size);
    }

    inline double bpe() const {
        return double(size()) / double(n); 
    }

};