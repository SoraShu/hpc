#include <stdio.h>
#include <stdlib.h>
#include "cblas.h"

int main()
{

    int n;      /*! array size */
    double da;  /*! double constant */
    double *dx; /*! input double array */
    int incx;   /*! input stride */
    double *dy; /*! output double array */
    int incy;   /*! output stride */

    int i;

    n = 10;
    da = 10;
    dx = (double *)malloc(sizeof(double) * n);
    incx = 1;
    dy = (double *)malloc(sizeof(double) * n);
    incy = 1;

    for (i = 0; i < n; i++)
    {
        dx[i] = 9 - i;
        dy[i] = i;
        printf("%f ", dy[i]); //输出原来的dy
    }
    printf("\n");

    cblas_daxpy(n, da, dx, incx, dy, incy); //运行daxpy程序
                                            //    cblas_dcopy(n, dx,incx, dy, incy);      //运行dcopy程序

    for (i = 0; i < n; i++)
    {
        printf("%f ", dy[i]); //输出计算后的dy
    }
    printf("\n");

    return 0;
}