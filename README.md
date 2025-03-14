# Paracomp

This repository is for my subject Paracomp para easy lang magpasa kay sir

## Requirements

### Tools and Libraries
- GCC with openMP support
- MPI implementation (e.g., MPICH or Open MPI)
- Python 3.x
- Matplotlib (Python library for plotting)
- Better to run this on WSL2/Linux 

## Running the program
After Completing the requirements just run the "run.sh" file

```bash
chmod +x run.sh
./run.sh
```

## Understanding the Graphs
The script will auto run the program and test some size and threads/cores performing matrix multiplication
and it will generate data and graph here's my example below, ofcourse if you run this program the data might be 
different due to the factor of your computer specs?

### Execution Time Comparison
The graph compares the execution times of matrix multiplication for different matrix sizes and the number of threads/processes used.

![Time_Comparison](/OpenMP_and_MPI_Execution_Time_Comparison.png)

### Speedup (S)
\[ S = \frac{T_1}{T_p} \]

![Speedup_Comparison](/OpenMP_and_MPI_Speedup_Comparison.png)

where \( T_1 \) is the execution time with 1 thread/process, and \( T_p \) is the execution time with \( p \) threads/processes.

### Efficiency (E)
\[ E = \frac{S}{p} = \frac{T_1}{p \cdot T_p} \]

![Efficiency_Comparison](/OpenMP_and_MPI_Efficiency_Comparison.png)

where \( S \) is the speedup and \( p \) is the number of threads/processes.

The graphs for speedup and efficiency illustrate the performance improvement and resource utilization for different configurations.
