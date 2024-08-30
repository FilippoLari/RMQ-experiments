#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>

template<typename T>
void write_uniform_sequence(const size_t n, const T lo, const T hi, const std::string &path) {
    std::ofstream file(path, std::ios::binary);

    if (!file) throw std::runtime_error("Unable to open the output file");

    std::uniform_int_distribution<T> uniform_dis(lo, hi);
    std::vector<T> values;

    std::random_device rd;
    std::mt19937 gen(rd());

    for(size_t i = 0; i < n; ++i)
        values.push_back(uniform_dis(gen));

    file.write(reinterpret_cast<const char*>(&n), sizeof(n));

    file.write(reinterpret_cast<const char*>(values.data()), n * sizeof(T));

    file.close();
}

template<typename T>
std::vector<T> deserialize(const std::string &path) {
    std::ifstream file(path, std::ios::binary);

    if (!file) throw std::runtime_error("Unable to open the output file");
    
    size_t n;

    file.read(reinterpret_cast<char*>(&n), sizeof(n));

    T* data = new T[n];

    file.read(reinterpret_cast<char*>(data), n * sizeof(T));

    file.close();

    std::vector<T> values(data, data + n);

    return values;
}


int main(int argc, char* argv[]) {

    write_uniform_sequence<int64_t>(100000000, 1, 1000000000, "test.bin");

    deserialize<int64_t>("test.bin");

    return 0;
}