#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

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

// Function to perform matrix multiplication using OpenMP
void matrix_multiply_openmp(__int128 **A, __int128 **B, __int128 **C, int N) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int N, T;

    printf("openMP_Process:\n\n");

    // Get the size of the matrix from the user
    printf("Enter the size of the matrix: ");
    scanf("%d", &N);
    
    // Get the number of threads
    T = omp_get_max_threads();

    // Dynamically allocate memory for the matrices
    __int128 **A = (__int128 **)malloc(N * sizeof(__int128 *));
    __int128 **B = (__int128 **)malloc(N * sizeof(__int128 *));
    __int128 **C = (__int128 **)malloc(N * sizeof(__int128 *));
    for (int i = 0; i < N; i++) {
        A[i] = (__int128 *)malloc(N * sizeof(__int128));
        B[i] = (__int128 *)malloc(N * sizeof(__int128));
        C[i] = (__int128 *)malloc(N * sizeof(__int128));
    }

    // Initialize matrices A and B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = i * N + j + 1;
            B[i][j] = i * N + j + 1;
        }
    }

    // Perform matrix multiplication
    double start_time = omp_get_wtime();
    matrix_multiply_openmp(A, B, C, N);
    double end_time = omp_get_wtime();

    printf("\nResult Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            print_int128(C[i][j]);
            putchar(' ');
        }
        putchar('\n');
    }

    printf("\nOpenMP Execution Time: %f seconds\n", end_time - start_time);

    FILE *f = fopen("openmp_times.txt", "a");
    fprintf(f, "Matrix Size: %d, Execution Time: %f seconds, Threads: %d\n", N, end_time - start_time, T);
    fclose(f);
    
    printf("\n\n\n");

    // Free the dynamically allocated memory
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
