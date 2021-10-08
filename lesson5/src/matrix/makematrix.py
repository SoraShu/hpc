import random

fa = open('matrixA.txt', 'w')
fb = open('matrixB.txt', "w")

for i in range(1024):
    for j in range(1024):
        fa.write(f'{random.random()*200-100} ')
        fb.write(f'{random.random()*200-100} ')
