import matplotlib.pyplot as plt

def read_times(filename):
    sizes = []
    times = {}
    with open(filename, "r") as file:
        for line in file:
            parts = line.strip().split(',')
            size = int(parts[0].split(':')[1].strip())
            time_str = parts[1].split(':')[1].strip()
            time = float(time_str.split()[0])  # Extract the numeric part before converting to float
            threads = int(parts[2].split(':')[1].strip())
            if size not in sizes:
                sizes.append(size)
            if threads not in times:
                times[threads] = []
            times[threads].append(time)
    return sizes, times

# Read OpenMP times
openmp_sizes, openmp_times = read_times("openmp_times.txt")

# Read MPI times
mpi_sizes, mpi_times = read_times("mpi_times.txt")

# Plot performance comparison
plt.figure(figsize=(12, 6))
markers = ['o', 's', 'D', '^', 'v', '<', '>', 'p', 'h']
colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k', '#1f77b4', '#ff7f0e',
          '#2ca02c', '#d62728', '#9467bd', '#8c564b', '#e377c2', '#7f7f7f', '#bcbd22', '#17becf']

# Plot OpenMP performance
for idx, (threads, times) in enumerate(openmp_times.items()):
    plt.plot(openmp_sizes, times, label=f'OpenMP {threads} Threads', marker=markers[idx % len(markers)], color=colors[idx])

# Plot MPI performance
for idx, (processes, times) in enumerate(mpi_times.items()):
    plt.plot(mpi_sizes, times, label=f'MPI {processes} Processes', marker=markers[idx % len(markers)], color=colors[idx + len(openmp_times)])

plt.xlabel('Matrix Size')
plt.ylabel('Execution Time (seconds)')
plt.title('OpenMP and MPI Performance Analysis')
plt.legend()
plt.show()
