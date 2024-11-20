#pragma once

#include <limits>
#include <cstdlib>
#include <climits>
#include <numeric>
#include <vector>

template<typename K, typename Pos>
class SparseTable {
    static_assert(std::is_integral_v<K>);
    static_assert(std::is_integral_v<Pos>);

    std::vector<std::vector<Pos>> st;
    std::vector<K> data;

    size_t n;

public:

    SparseTable() = default;

    explicit SparseTable(const std::vector<K> &data) : data(data), n(data.size()) {
        if(n == 0) [[unlikely]]
            return;

        st = std::vector<std::vector<Pos>>(n);
        const auto max_p = msb(n);

        for(auto i = 0; i < n; ++i) {
            st[i] = std::vector<Pos>(max_p + 1);
            st[i][0] = i;
        }
        
        for(auto j = 1; j <= max_p; ++j) {
            // rmq(i, i+(1<<j)-1) = min{rmq(i,i+(1<<(j-1))-1), rmq(i+(1<<(j-1)), i+(1<<j)-1)}
            for(auto i = 0; i + (1 << (j-1)) < n; ++i) {
                st[i][j] = (data[st[i][j-1]]<data[st[i+(1<<(j-1))][j-1]])? st[i][j-1] : st[i+(1<<(j-1))][j-1];
            }
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

        const auto k = msb(j - i + 1);

        return (data[st[i][k]]<data[st[j-(1<<k)+1][k]])? st[i][k] : st[j-(1<<k)+1][k]; 
    }

    inline size_t data_count() const {
        return n;
    }

    /**
     * Returns the size in bit of the data structure
     * @return the size in bit of the data structure
     */
    inline size_t size() const {
        return (st.size() * st[0].size() * sizeof(Pos)) * CHAR_BIT;
    }

    static constexpr std::string name() {
        return "SparseTable";
    }

    inline double bpe() const {
        return double(size()) / double(n); 
    }

private:

    /**
     * Returns the largest k such that 2^k <= len,
     * i.e. the most significant bit of x.
     * 
     * @param len the length of a range
     * @return the largest k such that 2^k <= len
     */
    inline uint msb(const size_t len) const { // todo: use sdsl
        const auto leading_zeroes = __builtin_clzll(len);
        return 63-leading_zeroes;
    }
};