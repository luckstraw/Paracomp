#!/bin/bash

# Create files for storing execution times
touch openmp_times.txt
touch mpi_times.txt
> openmp_times.txt
> mpi_times.txt

# Compile the OpenMP and MPI program
gcc -fopenmp openMP_matrix.c -o openMP_matrix
mpicc -o MPI_matrix MPI_matrix.c

# You can change the matrix sizes and number of threads/processes to test
matrix_sizes=(1000 1250 1500 1750)
threads=(1 2 3 4)

# MPI Performance Analysis
for N in "${matrix_sizes[@]}"; do
    for P in "${threads[@]}"; do
        mpirun -np $P ./MPI_matrix << EOF
$N
EOF
    done
done

# OpenMP Performance Analysis
for N in "${matrix_sizes[@]}"; do
    for T in "${threads[@]}"; do
        export OMP_NUM_THREADS=$T
        ./openMP_matrix << EOF
$N
EOF
    done
done

# For Graphs
python3 -m venv venv

source venv/bin/activate

python3 analyze_performance.py

deactivate
