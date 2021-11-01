#!/bin/bash

n=64

while(( $n<=1024 ))
do
        ./matmul $n
        let "n=n+64"
done