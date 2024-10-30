#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <benchmark_path> <datasets_path> <results_path>"
    exit 1
fi

BENCHMARK="$1" # Full path to the benchmark
DATA_DIR="$2" # Full path to the datasets directory
RES_DIR="$3" # Full path to where the results will be saved
QUERIES=10000

if [[ ! -f "$BENCHMARK" ]]; then
    echo "Error: $BENCHMARK not found!"
    exit 1
fi

if [[ ! -d "$DATA_DIR" ]]; then
    echo "Error: $DATA_DIR is not a valid directory!"
    exit 1
fi

if [[ ! -d "$RES_DIR" ]]; then
    echo "Error: $RES_DIR is not a valid directory!"
    exit 1
fi

echo "Running the benchmark on the uniform sequence..."
$BENCHMARK "$DATA_DIR/uniform_1B.bin" "$DATA_DIR/queries_1B.bin" $QUERIES "$RES_DIR/unif_build.csv" "$RES_DIR/unif_query.csv"
echo "Finished"

echo "Running the benchmark on the pseudo-increasing sequence (delta = 0)..."
$BENCHMARK "$DATA_DIR/pseudo_inc_1B_0.bin" "$DATA_DIR/queries_1B.bin" $QUERIES "$RES_DIR/pseudo_inc_0_build.csv" "$RES_DIR/pseudo_inc_0_query.csv"
echo "Finished"

echo "Running the benchmark on the pseudo-increasing sequence (delta = 100)..."
$BENCHMARK "$DATA_DIR/pseudo_inc_1B_100.bin" "$DATA_DIR/queries_1B.bin" $QUERIES "$RES_DIR/pseudo_inc_100_build.csv" "$RES_DIR/pseudo_inc_100_query.csv"
echo "Finished"

echo "Running the benchmark on the pseudo-increasing sequence (delta = 10000)..."
$BENCHMARK "$DATA_DIR/pseudo_inc_1B_10000.bin" "$DATA_DIR/queries_1B.bin" $QUERIES "$RES_DIR/pseudo_inc_10000_build.csv" "$RES_DIR/pseudo_inc_10000_query.csv"
echo "Finished"

echo "Running the benchmark on the pseudo-decreasing sequence (delta = 0)..."
$BENCHMARK "$DATA_DIR/pseudo_dec_1B_0.bin" "$DATA_DIR/queries_1B.bin" $QUERIES "$RES_DIR/pseudo_dec_0_build.csv" "$RES_DIR/pseudo_dec_0_query.csv"
echo "Finished"

echo "Running the benchmark on the pseudo-decreasing sequence (delta = 100)..."
$BENCHMARK "$DATA_DIR/pseudo_dec_1B_100.bin" "$DATA_DIR/queries_1B.bin" $QUERIES "$RES_DIR/pseudo_dec_100_build.csv" "$RES_DIR/pseudo_dec_100_query.csv"
echo "Finished"

echo "Running the benchmark on the pseudo-decreasing sequence (delta = 10000)..."
$BENCHMARK "$DATA_DIR/pseudo_dec_1B_10000.bin" "$DATA_DIR/queries_1B.bin" $QUERIES "$RES_DIR/pseudo_dec_10000_build.csv" "$RES_DIR/pseudo_dec_10000_query.csv"
echo "Finished"

echo "All runs completed, results are saved in $RES_DIR"
