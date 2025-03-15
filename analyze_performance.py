import matplotlib.pyplot as plt
import os

# Function to read times from a file
def read_times(filename):
    matrix_sizes = set()
    times = {}
    if not os.path.exists(filename):
        print(f"Error: {filename} does not exist.")
        return matrix_sizes, times
    with open(filename, "r") as file:
        for line in file:
            parts = line.strip().split(',')
            size = int(parts[0].split(':')[1].strip())  # Matrix size
            time_str = parts[1].split(':')[1].strip()
            time = float(time_str.split()[0])  # Extract numeric part before converting to float
            threads = int(parts[2].split(':')[1].strip())  # Threads/Processes
            matrix_sizes.add(size)
            if size not in times:
                times[size] = {}
            times[size][threads] = time  # Store execution time directly
    return sorted(matrix_sizes), times

# Function to calculate speedup and efficiency
def calculate_speedup_and_efficiency(times):
    speedup = {}
    efficiency = {}
    for size, thread_times in times.items():
        T1 = thread_times[1]  # Get time for 1 process/thread
        speedup[size] = {}
        efficiency[size] = {}
        for threads, t_time in thread_times.items():
            S = T1 / t_time
            speedup[size][threads] = S
            efficiency[size][threads] = S / threads
    return speedup, efficiency

# Read OpenMP and MPI data
openmp_sizes, openmp_times = read_times("openmp_times.txt")
mpi_sizes, mpi_times = read_times("mpi_times.txt")

# Calculate speedup and efficiency
openmp_speedup, openmp_efficiency = calculate_speedup_and_efficiency(openmp_times)
mpi_speedup, mpi_efficiency = calculate_speedup_and_efficiency(mpi_times)

# Common plot settings
markers = ['o', 's', 'D', '^', 'v', '<', '>', 'p']
colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k', '#1f77b4']

# 1. Plot Execution Time
plt.figure(figsize=(12, 6))
for idx, size in enumerate(openmp_sizes):
    threads = sorted(openmp_times[size].keys())
    times = [openmp_times[size][t] for t in threads]
    plt.plot(threads, times, label=f'OpenMP Matrix Size {size}', marker=markers[idx % len(markers)], color=colors[idx % len(colors)])
for idx, size in enumerate(mpi_sizes):
    threads = sorted(mpi_times[size].keys())
    times = [mpi_times[size][t] for t in threads]
    plt.plot(threads, times, label=f'MPI Matrix Size {size}', marker=markers[idx % len(markers)], color=colors[(idx + len(openmp_sizes)) % len(colors)])
plt.xlabel('Number of Threads/Processes')
plt.ylabel('Execution Time (seconds)')
plt.title('Execution Time vs Threads/Processes for Different Matrix Sizes')
plt.legend()
plt.tight_layout()
plt.show()

# 2. Plot Speedup
plt.figure(figsize=(12, 6))
for idx, size in enumerate(openmp_sizes):
    threads = sorted(openmp_speedup[size].keys())
    speedup_values = [openmp_speedup[size][t] for t in threads]
    plt.plot(threads, speedup_values, label=f'OpenMP Matrix Size {size}', marker=markers[idx % len(markers)], color=colors[idx % len(colors)])
for idx, size in enumerate(mpi_sizes):
    threads = sorted(mpi_speedup[size].keys())
    speedup_values = [mpi_speedup[size][t] for t in threads]
    plt.plot(threads, speedup_values, label=f'MPI Matrix Size {size}', marker=markers[idx % len(markers)], color=colors[(idx + len(openmp_sizes)) % len(colors)])
plt.xlabel('Number of Threads/Processes')
plt.ylabel('Speedup (S)')
plt.title('Speedup vs Threads/Processes for Different Matrix Sizes')
plt.legend()
plt.tight_layout()
plt.show()

# 3. Plot Efficiency
plt.figure(figsize=(12, 6))
for idx, size in enumerate(openmp_sizes):
    threads = sorted(openmp_efficiency[size].keys())
    efficiency_values = [openmp_efficiency[size][t] for t in threads]
    plt.plot(threads, efficiency_values, label=f'OpenMP Matrix Size {size}', marker=markers[idx % len(markers)], color=colors[idx % len(colors)])
for idx, size in enumerate(mpi_sizes):
    threads = sorted(mpi_efficiency[size].keys())
    efficiency_values = [mpi_efficiency[size][t] for t in threads]
    plt.plot(threads, efficiency_values, label=f'MPI Matrix Size {size}', marker=markers[idx % len(markers)], color=colors[(idx + len(openmp_sizes)) % len(colors)])
plt.xlabel('Number of Threads/Processes')
plt.ylabel('Efficiency (E)')
plt.title('Efficiency vs Threads/Processes for Different Matrix Sizes')
plt.legend()
plt.tight_layout()
plt.show()
