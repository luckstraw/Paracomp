#!/bin/bash

# Create files for storing execution times
touch openmp_times.txt
touch mpi_times.txt

# Clear any existing content in the files
> openmp_times.txt
> mpi_times.txt

# Compile the OpenMP program
gcc -fopenmp openMP_matrix.c -o openMP_matrix

# OpenMP Performance Analysis
for N in $(seq 25 25 1000); do
    export OMP_NUM_THREADS=4
    ./openMP_matrix << EOF
$N
EOF
done

# Compile the MPI program
mpicc MPI_matrix.c -o MPI_matrix

# MPI Performance Analysis
for N in $(seq 25 25 1000); do
    mpirun --oversubscribe -np 4 ./MPI_matrix << EOF
$N
EOF
done

# Run the Python script for graphical representation
python3 -m venv venv

source venv/bin/activate

python3 analyze_performance.py
