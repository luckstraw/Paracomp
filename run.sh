#!/bin/bash

# Create files for storing execution times
touch openmp_times.txt
touch mpi_times.txt
> openmp_times.txt
> mpi_times.txt

# Compile the OpenMP program
gcc -fopenmp openMP_matrix.c -o openMP_matrix

# Compile the MPI program
mpicc -o MPI_matrix MPI_matrix.c

# Matrix sizes to test
matrix_sizes=(100 200 300 400 500 600 700 800 900 1000)

# Number of threads/processes to test
threads=(1 2 4 8)

# OpenMP Performance Analysis
for N in "${matrix_sizes[@]}"; do
    for T in "${threads[@]}"; do
        export OMP_NUM_THREADS=$T
        ./openMP_matrix << EOF
$N
EOF
    done
done

# MPI Performance Analysis
for N in "${matrix_sizes[@]}"; do
    for P in "${threads[@]}"; do
        mpirun --oversubscribe -np $P ./MPI_matrix << EOF
$N
EOF
    done
done

# Set up and activate the virtual environment
python3 -m venv venv

source venv/bin/activate

# # Install matplotlib if not already installed
# pip install matplotlib

# Run the Python script for graphical representation
python analyze_performance.py

# Deactivate the virtual environment
deactivate
