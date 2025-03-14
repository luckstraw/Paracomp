# Compoile the OpenMP program
gcc -fopenmp openMP_matrix.c -o openMP_matrix

./openMP_matrix


# Compoile the MPI program
mpicc MPI_matrix.c -o MPI_matrix

mpirun -np 4 ./MPI_matrix
