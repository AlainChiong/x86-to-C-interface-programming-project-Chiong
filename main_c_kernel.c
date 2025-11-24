#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void distance_c(double* Z, double* X1, double* Y1, double* X2, double* Y2, int n) {
    int i;
    for (i = 0; i < n; i++) {
        double dx = X2[i] - X1[i];
        double dy = Y2[i] - Y1[i];
        Z[i] = sqrt(dx * dx + dy * dy);
    }
}

double time_c(int n, double* Z, double* X1, double* Y1, double* X2, double* Y2) {
    clock_t start = clock();
    distance_c(Z, X1, Y1, X2, Y2, n);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    printf("C KERNEL-- Sanity Check\n");
    double checkerX1[4] = { 1.5, 4.0, 3.5, 2.0 };
    double checkerX2[4] = { 3.0, 2.5, 2.5, 1.0 };
    double checkerY1[4] = { 4.0, 3.0, 3.5, 3.0 };
    double checkerY2[4] = { 2.0, 2.5, 1.0, 1.5 };
    double checkerZ[4];
    int n = 4;
    int t = 0;
    distance_c(checkerZ, checkerX1, checkerY1, checkerX2, checkerY2, n);
    printf("Z[%d] = %lf, %lf, %lf, %lf\n\n", t + 1, checkerZ[0], checkerZ[1], checkerZ[2], checkerZ[3]);
    
    int exponents[] = { 20, 24, 28 };
    srand(100);

    for (int k = 0; k < 3; k++) {
        long long n = (long long)pow(2, exponents[k]);
        printf("C KERNEL-- Size 2^%d (%lld elements)\n", exponents[k], n);

        double* X1 = (double*)malloc(n * sizeof(double));
        double* Y1 = (double*)malloc(n * sizeof(double));
        double* X2 = (double*)malloc(n * sizeof(double));
        double* Y2 = (double*)malloc(n * sizeof(double));
        double* Z = (double*)malloc(n * sizeof(double));

        for (int i = 0; i < n; i++) {
            X1[i] = (double)(rand() % 100); 
            Y1[i] = (double)(rand() % 100);
            X2[i] = (double)(rand() % 100); 
            Y2[i] = (double)(rand() % 100);
        }

        double total_time = 0.0;
        for (int t = 0; t < 30; t++) {
            total_time += time_c((int)n, Z, X1, Y1, X2, Y2);
        }

        printf("Average Time: %6f seconds\n\n", total_time / 30.0);
        printf("First 10 outputs: %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n\n", Z[0], Z[1], Z[2], Z[3], Z[4], Z[5], Z[6], Z[7], Z[8], Z[9]);
        free(X1); free(Y1); free(X2); free(Y2); free(Z);
    }
    return 0;
}