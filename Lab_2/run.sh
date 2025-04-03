#!/bin/bash

# Compile the OpenMP program
g++ -fopenmp parallel_weather.cpp -o weather_analysis

# Create or clear the output file
echo "Threads,Stations,Execution Time,Hottest Avg Temp,Coldest Avg Temp,Highest Temp,Highest Station" > weather_analysis.csv

# Define matrix sizes (number of stations to test)
matrix_sizes=(10000 20000 40000 80000 160000)

# Define number of threads to use(change this if you want)
export OMP_NUM_THREADS=16

# Loop through each matrix size and run the program
for NUM_STATIONS in "${matrix_sizes[@]}"; do
    # Pass the current matrix size as input to the program
    ./weather_analysis <<< "$NUM_STATIONS"
done
