#include <iostream>
#include <vector>

#include "generator.hpp"
#include "cxxopts.hpp"

int main(int argc, char* argv[]) {

    cxxopts::Options options("Generator", "Generates all the synthetic datasets used in our experiments");

    options.add_options()
        ("p,path", "Where to save the generated datasets", cxxopts::value<std::string>())
        ("h,help", "Print the usage instructions");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << "\n";
        return 0;
    }

    const std::string path = result["path"].as<std::string>();

    const size_t n = 1e9;
    const size_t q = 1e4;

    std::vector<int64_t> uniform_values = generate_uniform<int64_t>(n, 1, n);
    write_data<int64_t>(uniform_values, path+"/"+"uniform_1B.bin");

    std::vector<int64_t> pseudo_inc_10000 = generate_pseudo_increasing(n, 10000);
    write_data<int64_t>(pseudo_inc_10000, path+"/"+"pseudo_inc_1B_10000.bin");

    std::vector<int64_t> pseudo_dec_10000 = generate_pseudo_decreasing(n, 10000);
    write_data<int64_t>(pseudo_dec_10000, path+"/"+"pseudo_dec_1B_10000.bin");

    std::vector<size_t> ranges = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    std::vector<query_type> queries = generate_queries(n, q, ranges);

    write_data<query_type>(queries, path+"/"+"queries_1B.bin");
    
    return 0;
}