# Laboratory Activity # 2: Parallel Computing with OpenMP in C++

## Running the program

Follow these steps to execute the program:

1. **Make the code executable then run the program**:
```bash
chmod +x run.sh
```
```bash
./run.sh
```

## Output:
- **weather_analysis.csv will generate data**  

| Threads | Stations | Execution Time | Hottest Avg Temp | Coldest Avg Temp | Highest Temp | Highest Temp's Station |
| ------- | -------- | -------------- | ---------------- | ---------------- | ------------ | ---------------------- |
| 16 | 10000 | 0.00884068 | 22.2608 | 17.2799 | 39.99 | 6877 |
| 16 | 20000 | 0.0213205 | 22.2201 | 17.5402 | 39.99 | 3750 |
| 16 | 40000 | 0.0395823 | 22.5952 | 17.5165 | 39.99 | 35006 |
| 16 | 80000 | 0.110978 | 22.5317 | 17.5683 | 39.99 | 65007 |
| 16 | 160000 | 0.340577 | 22.9769 | 16.9109 | 39.99 | 50005 |

### **Assessment Questions**

### 1. What is OpenMP, and how does it improve program performance?
OpenMP (Open Multi-Processing) is an API for shared-memory parallel programming. It improves performance by enabling multi-threading, distributing tasks across multiple processor cores, and reducing execution time for computationally intensive programs.

### 2. How does #pragma omp parallel for work in the given program?
`#pragma omp parallel for` parallelizes the execution of the loop, dividing iterations among threads to run concurrently. This reduces the overall runtime by leveraging multi-core processing.

### 3. Compare execution time by running the program with and without OpenMP. What differences do you notice?
With OpenMP, execution time is significantly reduced as tasks are performed concurrently across multiple threads. Without OpenMP, execution is sequential, leading to longer runtime, particularly for larger datasets.

### 4. Modify the program to compute and display the hottest and coldest average temperatures recorded among all stations.
To compute the hottest and coldest average temperatures, iterate through the temperature matrix, calculate averages for each station, and track the maximum and minimum averages using shared variables protected by critical sections. (See the source Code)

### 5. What real-life applications can benefit from OpenMP-based parallel computing?
Applications include weather simulation, image processing, scientific modeling, financial data analysis, machine learning, and any domain involving large-scale computations or real-time processing.
