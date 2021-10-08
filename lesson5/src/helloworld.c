#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel
    printf("helloworld.\n");
    return 0;
}