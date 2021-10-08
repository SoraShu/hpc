#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main()
{
    int i, N = 1000;
    int a[N], b[N], c[N];

#pragma omp parallel for
    for (i = 0; i < 1000; i++)
    {
        a[i] = i;
        b[i] = i * i;
        c[i] = a[i] + b[i];
        sleep(0.1);
    }
    return 0;
}