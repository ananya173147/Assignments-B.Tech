For the programs to get executed, user must create a text file named "inp.txt" in the same directory as the source code file. This will contain two digits, n and p, which indicate the size of the array as 2^n and the number of threads as 2^p respectively.

To compile the code, type the following in the terminal:
gcc -pthread -o Asgn1_CS19B1004_mth1 Asgn1_CS19B1004_mth1.c
gcc -pthread -o Asgn1_CS19B1004_mth2 Asgn1_CS19B1004_mth2.c

To execute the program, type the following in the terminal:
./Asgn1_CS19B1004_mth1
./Asgn1_CS19B1004_mth2

This will create a text file named "output.txt" which contains the array before sorting, after sorting and the time taken for sorting in microseconds.
Ex:
8 15 22 13 16 27 
8 13 15 16 22 27 
Time taken: 563 Microseconds.
