#include <stdio.h>
#include <time.h>
#include "cblas.h"

#define MaxN 1024
#define a(i, j) A[i * ld + j]
#define b(i, j) B[i * ld + j]
#define c(i, j) C[i * ld + j]
double A[MaxN * MaxN];
double B[MaxN * MaxN];
double C[MaxN * MaxN];
int ld;

void readMatrix(double *a, FILE *f)
{
    for (int i = 0; i < MaxN; ++i)
    {
        fscanf(f, "%lf", a + i);
    }
}

void mymatmul(int N)
{
    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                c(i, j) += a(i, k) * b(k, j);
}

void cblasmatmul(int N)
{
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1, A, N, B, N, 1, C, N);
}

int main()
{
    FILE *fa = fopen("../matrix/matrixA.txt", "r");
    FILE *fb = fopen("../matrix/matrixB.txt", "r");
    readMatrix(A, fa);
    readMatrix(B, fb);
    clock_t start_t, end_t;
    double t1, t2;
    FILE *out = fopen("../matrix/data.csv", "w");
    fprintf(out, "N,my,GEMM\n");
    ld = 20;
    for (; ld < MaxN; ld += 20)
    {
        start_t = clock();
        mymatmul(ld);
        end_t = clock();
        t1 = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        start_t = clock();
        cblasmatmul(ld);
        end_t = clock();
        t2 = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        fprintf(out, "%d,%lf,%lf\n", ld, t1, t2);
    }
    return 0;
}
