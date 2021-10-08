#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MaxN 1024
#define a(i, j) A[i * ld + j]
#define b(i, j) B[i * ld + j]
#define c(i, j) C[i * ld + j]
double A[MaxN * MaxN];
double B[MaxN * MaxN];
double C[MaxN * MaxN];
int ld;

typedef struct
{
    int N, l, r;
} arg;

arg x[4];

void readMatrix(double *a, FILE *f)
{
    for (int i = 0; i < MaxN; ++i)
    {
        fscanf(f, "%lf", a + i);
    }
}

void single_thread_matmul(int N)
{

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                c(i, j) += a(i, k) * b(k, j);
}

void calc(arg *x)
{
    int N = x->N;
    for (int i = x->l; i < x->r; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                c(i, j) += a(i, k) * b(k, j);
}

void multi_thread_matmul(int N)
{
    pthread_t t[4];
    int len = N / 4;
    for (int i = 0; i < 4; ++i)
    {
        x[i].N = N;
        x[i].l = i * len;
        x[i].r = (i + 1) * len;
        if (pthread_create(&t[i], NULL, (void *)calc, &x[i]) != 0)
        {
            printf("failed to create a thread.\n");
            exit(0);
        }
    }

    for (int i = 0; i < 4; ++i)
        pthread_join(t[i], NULL);
}

int main()
{
    FILE *fa = fopen("./matrix/matrixA.txt", "r");
    FILE *fb = fopen("./matrix/matrixB.txt", "r");
    readMatrix(A, fa);
    readMatrix(B, fb);
    //clock_t start_t, end_t;
    //time_t start_t, end_t;
    struct timeval start_t, end_t;
    double t1, t2;
    FILE *out = fopen("./matrix/data.csv", "w");
    fprintf(out, "N,single_thread,multi_thread\n");
    ld = 32;
    for (; ld <= MaxN; ld += 32)
    {
        gettimeofday(&start_t, NULL);
        single_thread_matmul(ld);
        gettimeofday(&end_t, NULL);
        t1 = (end_t.tv_sec - start_t.tv_sec) + (end_t.tv_usec - start_t.tv_usec) / 1000000.0;
        gettimeofday(&start_t, NULL);
        multi_thread_matmul(ld);
        gettimeofday(&end_t, NULL);
        t2 = (end_t.tv_sec - start_t.tv_sec) + (end_t.tv_usec - start_t.tv_usec) / 1000000.0;
        fprintf(out, "%d,%lf,%lf\n", ld, t1, t2);
    }
    return 0;
}
