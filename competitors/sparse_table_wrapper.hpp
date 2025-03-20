#pragma once

#include <limits>
#include <cstdlib>
#include <climits>
#include <numeric>
#include <vector>

#include <sdsl/int_vector.hpp>
#include <sdsl/bits.hpp>
#include <sdsl/util.hpp>

template<typename K>
class SparseTableWrapper
{
    std::vector<sdsl::int_vector<>> table;
    std::vector<K> data;
    size_t n;

public:
    
    SparseTableWrapper() = default;

    explicit SparseTableWrapper(const std::vector<K> &data) : data(data), n(data.size()) {
        if(data.size() == 0) [[unlikely]]
            return;

        const size_t n = data.size();

        const size_t lg_n = sdsl::bits::hi(n);
        table.resize(lg_n);

        for (size_t i = 0; i < lg_n; ++i) {
            table[i] = sdsl::int_vector<>(n - (1ULL << (i + 1)) + 1, 0, i + 1);
        }

        for (size_t i = 0; i < n - 1; ++i) {
            if(data[i+1] < data[i]) 
                table[0][i] = 1;
        }

        for (size_t i = 1; i < lg_n; ++i) {
            for (size_t j = 0; j < table[i].size(); ++j) {
                table[i][j] = (data[j+table[i-1][j]] <= data[j+(1ULL<<i)+table[i-1][j+(1ULL<<i)]]) 
                                    ? table[i-1][j] : (1ULL<<i)+table[i-1][j+(1ULL<<i)];                      
            }
        }

        for(auto &row : table)
            sdsl::util::bit_compress(row);
    }

    inline size_t query(const size_t i, const size_t j) const {
        assert(i <= j);
        if (i == j) [[unlikely]]
            return i;
        if(i + 1 == j) [[unlikely]]
            return (data[i] < data[j]) ? i : j;
        const size_t k = sdsl::bits::hi(j - i);
        const size_t jj = j - (1ULL << k) + 1;
        return (data[i+table[k-1][i]] <= data[jj+table[k-1][jj]]) ? i+table[k-1][i] : jj+table[k-1][jj];
    }

    static constexpr std::string name() {
        return "SparseTable";
    }

    inline size_t size() const {
        size_t table_size = 0;
        for(const auto &row : table)
            table_size += row.bit_size();
        return table_size + ((sizeof(data) + sizeof(n)) * CHAR_BIT);
    }

    inline double bpe() const {
        return double(size()) / double(n);
    }
};
