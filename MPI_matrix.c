#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Custom function to print __int128
void print_int128(__int128 value) {
    if (value < 0) {
        putchar('-');
        value = -value;
    }
    if (value == 0) {
        putchar('0');
        return;
    }

    char buffer[40]; // Buffer to hold the digits
    int i = 0;
    while (value > 0) {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    }
    while (i > 0) {
        putchar(buffer[--i]);
    }
}

void matrix_multiply_mpi(__int128 *A, __int128 *B, __int128 *C, int N, int rank, int size) {
    int rows_per_process = N / size;
    int extra_rows = N % size;
    int start = rank * rows_per_process + (rank < extra_rows ? rank : extra_rows);
    int end = start + rows_per_process + (rank < extra_rows ? 1 : 0);

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
            int rows = rows_per_process + (i < extra_rows ? 1 : 0);
            recvcounts[i] = rows * N;
            displs[i] = offset;
            offset += rows * N;
        }
    }

    MPI_Datatype mpi_int128;
    MPI_Type_contiguous(2, MPI_LONG_LONG_INT, &mpi_int128);
    MPI_Type_commit(&mpi_int128);

    MPI_Gatherv(&C[start * N], (end - start) * N, mpi_int128, C, recvcounts, displs, mpi_int128, 0, MPI_COMM_WORLD);

    MPI_Type_free(&mpi_int128);

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

    __int128 *A = (__int128 *)malloc(N * N * sizeof(__int128));
    __int128 *B = (__int128 *)malloc(N * N * sizeof(__int128));
    __int128 *C = (__int128 *)malloc(N * N * sizeof(__int128));

    if (rank == 0) {
        for (int i = 0; i < N * N; i++) {
            A[i] = i + 1;
            B[i] = i + 1;
        }
    }

    MPI_Datatype mpi_int128;
    MPI_Type_contiguous(2, MPI_LONG_LONG_INT, &mpi_int128);
    MPI_Type_commit(&mpi_int128);

    MPI_Bcast(A, N * N, mpi_int128, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, N * N, mpi_int128, 0, MPI_COMM_WORLD);

    double start_time = MPI_Wtime();
    matrix_multiply_mpi(A, B, C, N, rank, size);
    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("\nResult Matrix:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                print_int128(C[i * N + j]);
                putchar(' ');
            }
            putchar('\n');
        }
        printf("\nMPI Execution Time: %f seconds\n", end_time - start_time);

        FILE *f = fopen("mpi_times.txt", "a");
        fprintf(f, "Matrix Size: %d, Execution Time: %f seconds, Processes: %d\n", N, end_time - start_time, size);
        fclose(f);
    }

    free(A);
    free(B);
    free(C);

    MPI_Type_free(&mpi_int128);
    MPI_Finalize();
    return 0;
}
