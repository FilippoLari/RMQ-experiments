# RMQ Experiments

## Requirements

* `CMake >= 3.25`

## Build the Project

```bash
git clone git@github.com:FilippoLari/RMQ-Experiments.git
cd RMQ-Experiments/
git submodule update --init --recursive

rm competitors/FL-RMQ/libsais/VERSION
cd competitors/succinct/
cmake . -DCMAKE_POLICY_VERSION_MINIMUM=3.5 && make -j8
cd ../../
mkdir build
cd build/
cmake ..; make -j8
```

## Generate Queries

To generate queries for the benchmark, run:

```bash
./benchmark/generator -p <path_to_folder> -s <output_filename> -n <dataset_size> -q <number_of_queries>
```

Arguments:

* `-p`: folder where the query file will be saved
* `-s`: name of the output file
* `-n`: size of the dataset
* `-q`: number of queries to generate (sizes: 10, 100, 1k, 10k, 100k, 1M, 10M)

## Run the Benchmark

```bash
cd build/
./benchmark/benchmark -s <dataset> -q <queries> -n <num_queries> -b <build_results_file> -t <query_results_file>
```

Arguments:

* `-s`: dataset file (can be plain text or a binary LCP array of `int64_t`)
* `-q`: binary file containing queries (must be generated using the generator above)
* `-n`: number of queries in the query file
* `-b`: output file for build-time results (time + space)
* `-t`: output file for query-time results (average time + space)

## Generate LCP file

Optionally, you can compute the LCP array of a text file and save it for use in the benchmark.

```
cd build/
./benchmark/lcp_builder <text_file>
```

The only argument is the text file. The executable will generate a binary file of `int64_t` named `<text_file>.lcp`.
