#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void matrix_multiply_mpi(int *A, int *B, int *C, int N, int rank, int size) {
    int rows_per_process = N / size;
    int extra_rows = N % size;
    int start = rank * rows_per_process + (rank < extra_rows ? rank : extra_rows);
    int end = start + rows_per_process + (rank < extra_rows);

    for (int i = start; i < end; i++) {
        for (int j = 0; j < N; j++) {
            C[i * N + j] = 0;
            for (int k = 0; k < N; k++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
    
    int *recvcounts = NULL, *displs = NULL;
    if (rank == 0) {
        recvcounts = (int *)malloc(size * sizeof(int));
        displs = (int *)malloc(size * sizeof(int));
        for (int i = 0, offset = 0; i < size; i++) {
            int rows = rows_per_process + (i < extra_rows);
            recvcounts[i] = rows * N;
            displs[i] = offset;
            offset += rows * N;
        }
    }
    
    MPI_Gatherv(&C[start * N], (end - start) * N, MPI_INT, C, recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        free(recvcounts);
        free(displs);
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N;
    if (rank == 0) {
        printf("\nMPI Process:\n\n");
        printf("Enter matrix size (N): ");
        fflush(stdout);
        scanf("%d", &N);
    }
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int *A = (int *)malloc(N * N * sizeof(int));
    int *B = (int *)malloc(N * N * sizeof(int));
    int *C = (int *)malloc(N * N * sizeof(int));

    if (rank == 0) {
        for (int i = 0; i < N * N; i++) {
            A[i] = i + 1;
            B[i] = i + 1;
        }
    }
    MPI_Bcast(A, N * N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    double start_time = MPI_Wtime();
    matrix_multiply_mpi(A, B, C, N, rank, size);
    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Matrix A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", A[i * N + j]);
            }
            printf("\n");
        }
        
        printf("\nMatrix B:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", B[i * N + j]);
            }
            printf("\n");
        }
        
        printf("\nResult Matrix:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", C[i * N + j]);
            }
            printf("\n");
        }
        printf("\nMPI Execution Time: %f seconds\n", end_time - start_time);

        FILE *f = fopen("mpi_times.txt", "a");
        fprintf(f, "Matrix Size: %d, Execution Time: %f seconds\n", N, end_time - start_time);
        fclose(f);
    }
    
    free(A);
    free(B);
    free(C);

    MPI_Finalize();
    return 0;
}