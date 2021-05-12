import numpy as np
import random
import math

no_threads, n = input().split()
no_threads = int(no_threads)
n = int(n)

def empty(x, y):
    return x*0

b = np.fromfunction(empty, (n, n), dtype = int)

for i in range(0, n):
    for j in range(0, n):
        if i == j:
            b[i][j] = 0
        else:
            switch = random.random()
            random.seed()
            if switch > random.random():
                a = random.randrange(0,2)
                b[i][j] = a
                b[j][i] = a
            else:
                b[i][j] = 0
                b[j][i] = 0

def print_array(arr):
    for a in arr:
        for elem in a:
            print("{}".format(elem).rjust(2), end="")
        print(end="\n")

print(no_threads,n)
print_array(b)
