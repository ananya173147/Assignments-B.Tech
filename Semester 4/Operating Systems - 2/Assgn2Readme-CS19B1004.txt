Make sure the input file "inp-params.txt" is in the same folder as the source code files.

It is of the following format:
3                       //number of processes = n
1 5 10 10               //n lines of input, each containing: process id, processsing time, period, repeats
2 3 15 10               
3 4 15 10

To compile:
g++ Assgn2-RMSCS19B1004.cpp -o rms
g++ Assgn2-EDFCS19B1004.cpp -o edf

To run:
./rms
./edf

After running, RMS-Log.txt, EDF-Log.txt consisting of discrete events, of each algorithm, and RM-Stats.txt, EDF-Stats.txt consisting of the average waiting time and deadlines missed of both the algorithms are generated.