#!/bin/bash
echo start
gcc -E  matrix.c -o matrix.i -lopenblas
gcc -S  matrix.i -o matrix.s -lopenblas
gcc -c matrix.s -o matrix.o -lopenblas
gcc matrix.o -o matrix -lopenblas
./matrix
echo end
