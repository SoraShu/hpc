#!/bin/bash

n=64

while(( $n<=1024 ))
do
        mpirun -n 10 ./mpi_matmul $n
        let "n=n+64"
done