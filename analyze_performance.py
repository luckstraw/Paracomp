import matplotlib.pyplot as plt

# Read OpenMP times
openmp_sizes = []
openmp_times = []
with open("openmp_times.txt", "r") as file:
    for line in file:
        parts = line.strip().split(',')
        size = int(parts[0].split(':')[1].strip())
        time = float(parts[1].split(':')[1].strip().split()[0])
        openmp_sizes.append(size)
        openmp_times.append(time)

# Read MPI times
mpi_sizes = []
mpi_times = []
with open("mpi_times.txt", "r") as file:
    for line in file:
        parts = line.strip().split(',')
        size = int(parts[0].split(':')[1].strip())
        time = float(parts[1].split(':')[1].strip().split()[0])
        mpi_sizes.append(size)
        mpi_times.append(time)

base_time = openmp_times[0]
openmp_speedup = [base_time / time for time in openmp_times]
mpi_speedup = [base_time / time for time in mpi_times]
openmp_efficiency = [(s / 4) * 100 for s in openmp_speedup]
mpi_efficiency = [(s / 4) * 100 for s in mpi_speedup]

plt.figure(figsize=(12, 6))

# Plot speedup
plt.subplot(1, 2, 1)
plt.plot(openmp_sizes, openmp_speedup, label='OpenMP Speedup')
plt.plot(mpi_sizes, mpi_speedup, label='MPI Speedup')
plt.xlabel('Matrix Size')
plt.ylabel('Speedup')
plt.title('Speedup Analysis')
plt.legend()

# Plot efficiency
plt.subplot(1, 2, 2)
plt.plot(openmp_sizes, openmp_efficiency, label='OpenMP Efficiency')
plt.plot(mpi_sizes, mpi_efficiency, label='MPI Efficiency')
plt.xlabel('Matrix Size')
plt.ylabel('Efficiency (%)')
plt.title('Efficiency Analysis')
plt.legend()

plt.tight_layout()
plt.show()
