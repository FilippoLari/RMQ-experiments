## Benchmark setup

```bash
git clone https://github.com/FilippoLari/RMQ-experiments
cd RMQ-experiments
git submodule init
git submodule --update --force
```

Build FL-RMQ, Succinct and sdsl-lite separately.

```
mkdir build
cd build
cmake ..
make -j8
```

## Generating the datasets

Use `generator` to generate the artificial datasets.

## Running the benchmark

Use the script `run_experiments.sh` to run the benchmark. 