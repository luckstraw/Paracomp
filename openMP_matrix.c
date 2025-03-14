#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function to perform matrix multiplication using OpenMP
void matrix_multiply_openmp(int **A, int **B, int **C, int N) {
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
    int N;

    printf("openMP_Process:\n\n");

    // Get the size of the matrix from the user
    printf("Enter the size of the matrix: ");
    scanf("%d", &N);

    // Dynamically allocate memory for the matrices
    int **A = (int **)malloc(N * sizeof(int *));
    int **B = (int **)malloc(N * sizeof(int *));
    int **C = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
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

    // Print matrices and the result
    printf("Matrix A:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nMultiplied by\n");
    
    printf("\nMatrix B:\n");
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
    printf("\nOpenMP Execution Time: %f seconds\n", end_time - start_time);

    FILE *f = fopen("openmp_times.txt", "a");
    fprintf(f, "Matrix Size: %d, Execution Time: %f seconds\n", N, end_time - start_time);
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
