# Laboratory Activity # 1: Performance Analysis in Parallel and Distributed Computing

This lab activity explores the performance of parallel and distributed systems by analyzing **execution time**, **speedup**, and **efficiency** using **OpenMP** and **MPI**. It helps evaluate scalability and resource utilization across different workloads.

---

## Requirements

### Tools and Libraries
- GCC with openMP support
- MPI implementation (e.g., MPICH or Open MPI)
- Python 3.x
- Matplotlib (Python library for plotting)
- Bash

## Running the program
Make sure you have the requirements before proceeding

1. **Clone the repository then navigate to the directory**:
```bash
git clone https://github.com/luckstraw/Paracomp.git
```
```bash
cd Paracomp
```
2. **Make the code executable then run the program**:
```bash
chmod +x run.sh
```
```bash
./run.sh
```
After running the program it will generate a data in `.txt` file and it will show you a graph of your generated data. You can adjust the matrix size and the number of threads/cores in `run.sh` file

---

## Understanding the Graphs
This graph here is the result of my generated data, the data you generated might be different on this due to some factor like computer cpu core/threads 

### Execution Time Comparison
The graph compares the execution times of matrix multiplication for different matrix sizes and the number of threads/processes used.

![Time_Comparison](/assets/Execution_Time.png)

---

### Speedup (S)

Speedup measures the performance improvement when executing a task using multiple threads or processes compared to a single-threaded execution.

**Formula**:

```math
S = \frac{T_1}{T_p}
```
Where:
- $\( T_1 \)$: Execution time of the task on a single thread or process.
- $\( T_p \)$: Execution time of the task on $\( p \)$ threads or processes.

**Description**:
- A **higher speedup** indicates better performance, as the task is completed faster when more threads/processes are used.
- Ideally, \( S \) should be equal to the number of threads or processes \( p \) (i.e., **linear speedup**). However, due to communication overhead, synchronization, and non-parallelizable portions of the task, the actual speedup is often less than \( p \).

![Speedup](/assets/Speedup.png)

---

### Efficiency (E)

Efficiency measures how effectively the computational resources (threads or processes) are utilized during parallel execution.

**Formula**:
```math
E = \frac{S}{p} = \frac{T_1}{p \cdot T_p}
```
Where:
- $\( S \)$: Speedup.
- $\( p \)$: Number of threads or processes.

**Description**:
- Efficiency ranges from 0 to 1 (or 0% to 100%):
  - $\( E = 1 \)$ (or 100%) implies perfect utilization of resources.
  - $\( E < 1 \)$ indicates some loss in resource efficiency, often due to communication overhead, load imbalance, or sequential portions of the workload.

![Efficiency](/assets/Efficiency.png)