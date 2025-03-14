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

def calculate_speedup_and_efficiency(times):
    speedup = {}
    efficiency = {}
    for threads, t_times in times.items():
        T1 = t_times[0]  # Execution time with 1 thread/process
        speedup[threads] = [T1 / t for t in t_times]
        efficiency[threads] = [S / threads for S in speedup[threads]]
    return speedup, efficiency

# Read and calculate OpenMP times, speedup, and efficiency
openmp_sizes, openmp_times = read_times("openmp_times.txt")
openmp_speedup, openmp_efficiency = calculate_speedup_and_efficiency(openmp_times)

# Read and calculate MPI times, speedup, and efficiency
mpi_sizes, mpi_times = read_times("mpi_times.txt")
mpi_speedup, mpi_efficiency = calculate_speedup_and_efficiency(mpi_times)

# Plot execution time comparison
plt.figure(figsize=(12, 6))
markers = ['o', 's', 'D', '^', 'v', '<', '>', 'p', 'h']
colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k', '#1f77b4', '#ff7f0e',
          '#2ca02c', '#d62728', '#9467bd', '#8c564b', '#e377c2', '#7f7f7f', '#bcbd22', '#17becf']

for idx, (threads, t_times) in enumerate(openmp_times.items()):
    plt.plot(openmp_sizes, t_times, label=f'OpenMP {threads} Threads', marker=markers[idx % len(markers)], color=colors[idx])
for idx, (processes, t_times) in enumerate(mpi_times.items()):
    plt.plot(mpi_sizes, t_times, label=f'MPI {processes} Processes', marker=markers[idx % len(markers)], color=colors[idx + len(openmp_times)])

plt.xlabel('Matrix Size')
plt.ylabel('Execution Time (seconds)')
plt.title('OpenMP and MPI Execution Time Comparison')
plt.legend()
plt.show()

# Plot speedup comparison
plt.figure(figsize=(12, 6))

for idx, (threads, s_values) in enumerate(openmp_speedup.items()):
    plt.plot(openmp_sizes, s_values, label=f'OpenMP {threads} Threads', marker=markers[idx % len(markers)], color=colors[idx])
for idx, (processes, s_values) in enumerate(mpi_speedup.items()):
    plt.plot(mpi_sizes, s_values, label=f'MPI {processes} Processes', marker=markers[idx % len(markers)], color=colors[idx + len(openmp_times)])

plt.xlabel('Matrix Size')
plt.ylabel('Speedup (S)')
plt.title('OpenMP and MPI Speedup Comparison')
plt.legend()
plt.text(0.95, 0.01, 'Speedup (S) = T1 / Tp', verticalalignment='bottom', horizontalalignment='right', transform=plt.gca().transAxes, color='black', fontsize=12)
plt.show()

# Plot efficiency comparison
plt.figure(figsize=(12, 6))

for idx, (threads, e_values) in enumerate(openmp_efficiency.items()):
    plt.plot(openmp_sizes, e_values, label=f'OpenMP {threads} Threads', marker=markers[idx % len(markers)], color=colors[idx])
for idx, (processes, e_values) in enumerate(mpi_efficiency.items()):
    plt.plot(mpi_sizes, e_values, label=f'MPI {processes} Processes', marker=markers[idx % len(markers)], color=colors[idx + len(openmp_times)])

plt.xlabel('Matrix Size')
plt.ylabel('Efficiency (E)')
plt.title('OpenMP and MPI Efficiency Comparison')
plt.legend()
plt.text(0.95, 0.01, 'Efficiency (E) = S / p', verticalalignment='bottom', horizontalalignment='right', transform=plt.gca().transAxes, color='black', fontsize=12)
plt.show()
