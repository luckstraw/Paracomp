// MPI Implementation (mpi_matrix.c)
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 4  // Matrix size

void matrix_multiply_mpi(int A[N][N], int B[N][N], int C[N][N], int rank, int size) {
    int rows_per_process = N / size;
    int start = rank * rows_per_process;
    int end = start + rows_per_process;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    MPI_Gather(&C[start][0], rows_per_process * N, MPI_INT, &C[0][0], rows_per_process * N, MPI_INT, 0, MPI_COMM_WORLD);
}

int main(int argc, char *argv[]) {
    int A[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    int B[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    int C[N][N] = {0};

    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    double start_time = MPI_Wtime();
    matrix_multiply_mpi(A, B, C, rank, size);
    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("MPI Process:\n\n");
        printf("Matrix A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", A[i][j]);
            }
            printf("\n");
        }
        printf("Multiplied by\n\n");
        printf("Matrix B:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", B[i][j]);
            }
            printf("\n");
        }
        printf("\nResult Matrix:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
        printf("\nMPI Execution Time: %f seconds\n", end_time - start_time);
    }
    MPI_Finalize();
    return 0;
}
