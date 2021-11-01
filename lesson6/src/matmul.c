#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#define MaxN 1024
#define a(i, j) A[i * n + j]
#define b(i, j) B[i * n + j]
#define c(i, j) C[i * n + j]
double A[MaxN * MaxN];
double B[MaxN * MaxN];
double C[MaxN * MaxN];
int n;

void readMatrix(double *a, FILE *f)
{
    for (int i = 0; i < MaxN; ++i)
    {
        fscanf(f, "%lf", a + i);
    }
}

void matmul(int N)
{

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                c(i, j) += a(i, k) * b(k, j);
}

int main(int argc, char *argv[])
{
    FILE *fa = fopen("./matrix/matrixA.txt", "r");
    FILE *fb = fopen("./matrix/matrixB.txt", "r");
    readMatrix(A, fa);
    readMatrix(B, fb);
    n = atoi(argv[1]);
    int len = strlen(argv[1]);
    struct timeval start, end;
    gettimeofday(&start, 0);
    matmul(n);
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;
    printf("%d,%lf\n", n, elapsed);
    return 0;
}