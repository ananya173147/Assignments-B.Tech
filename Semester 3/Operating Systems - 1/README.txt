List of files submitted: 
1) matmul.c
2) MatMul - Report.pdf
3) README.txt

The program must be compiled in the following manner:
$ gcc matmul.c -pthread -o matmul 

Syntax for input time (Non-Interactive Mode):
./matmul --ar <rows_in_A> --ac <cols_in_A> --br <rows_in_B> --bc <cols_in_B>

Ex: ./matmul --ar 3 --ac 4 --br 4 --bc 5

Time taken for single threaded: 3 us
Time taken for multi process: 1 us
Time taken for multi threaded: 545 us
Speedup for multi process : 3.00 x
Speedup for multi threaded : 0.01 x

Syntax for input time (Interactive Mode):
./matmul --ar <rows_in_A> --ac <cols_in_A> --br <rows_in_B> --bc <cols_in_B> [--interactive]

Then enter the elements of matrices A and B respectively, either with spaces or enter separating the matrix elements. The resultant matrix will be printed out.

Ex: ./matmul --ar 3 --ac 4 --br 4 --bc 5 --interactive

Enter A:
2 3 4
4 3 4
5 3 7
Enter B:
1 0 0
0 1 0
0 0 1
Result:
2 3 4
4 3 4
5 3 7