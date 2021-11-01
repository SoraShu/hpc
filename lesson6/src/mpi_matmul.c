#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

void readMatrix(double **m, FILE *f, int siz)
{
    for (int i = 0; i < siz; ++i)
    {
        for (int j = 0; j < siz; ++j)
        {
            fscanf(f, "%lf", &m[i][j]);
        }
    }
}

double **createMatrix(int siz)
{
    double **a = (double **)malloc(sizeof(double *) * 1024);
    for (int i = 0; i < siz; ++i)
    {
        a[i] = (double *)malloc(sizeof(double *) * 1024);
        memset(a[i], 0, sizeof(double));
    }
    return a;
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    double **a = createMatrix(n);
    double **b = createMatrix(n);
    double **c = createMatrix(n);
    FILE *fmatrixA = fopen("./matrix/matrixA.txt", "r");
    FILE *fmatrixB = fopen("./matrix/matrixB.txt", "r");
    readMatrix(a, fmatrixA, n);
    readMatrix(b, fmatrixB, n);
    int numprocs, myid, source;
    MPI_Status status;

    struct timeval start, end;
    gettimeofday(&start, 0);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    if (myid != 0)
    {
        double *ans = malloc(sizeof(double) * n);
        for (int p = myid - 1; p < n; p += (numprocs - 1))
        {
            for (int j = 0; j < n; ++j)
            {
                ans[j] = 0;
                for (int k = 0; k < n; ++k)
                {
                    ans[j] += a[p][k] * b[k][j];
                }
            }
            MPI_Send(ans, n, MPI_DOUBLE, 0, p, MPI_COMM_WORLD);
        }
    }
    else
    {
        for (source = 1; source < numprocs; source++)
        {
            for (int p = source - 1; p < n; p += (numprocs - 1))
            {
                MPI_Recv(c[p], n, MPI_DOUBLE, source, p, MPI_COMM_WORLD, &status);
            }
        }
        gettimeofday(&end, 0);
        long seconds = end.tv_sec - start.tv_sec;
        long microseconds = end.tv_usec - start.tv_usec;
        double elapsed = seconds + microseconds * 1e-6;
        printf("%d,%lf\n", n, elapsed);
    }
    sleep(30);
    MPI_Finalize();
    return 0;
}