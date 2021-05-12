//
//  main.c
//  OS_A1
//
//  Created by Siddharth Gorayan on 31/01/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

typedef struct arg
{
    long* array;
    int start;
    int end;
}segment;

void merge(long a[], int start, int mid, int end)
{
    int i, j, k, m, n;
    m = mid - start + 1;
    n = end - mid;
    long Array[m];
    
    long Brray[n];
    for(i=0;i<m;i++)
    {
        Array[i] = a[start+i];
    }
    for(j=0;j<n;j++)
    {
        Brray[j] = a[mid+1+j];
    }
    i = 0;
    j = 0;
    k = start;
    while(i<m && j<n)
    {
        if(Array[i]<=Brray[j])
        {
            a[k] = Array[i];
            i++;
        }
        else
        {
            a[k] = Brray[j];
            j++;
        }
        k++;
    }
    while (i < m)
    {
        a[k] = Array[i];
        i++;
        k++;
    }
    while (j < n)
    {
        a[k] = Brray[j];
        j++;
        k++;
    }
}

/* Merge Sort function to sort the values of the array. */
int mergeSort(long a[], int start, int end)
{
    int mid;
    if(start<end)
    {
        mid = start + (end - start)/2;
        mergeSort(a, start, mid);
        mergeSort(a, mid+1, end);
        merge(a, start, mid, end);
    }
    return 0;
}


void* sortMultiThreadM1(void* arg)
{
    struct arg* segment = (struct arg*) arg;

    int mid = segment->start + (segment->end-segment->end)/2;
    
    if(segment->start<segment->end)
    {
        mergeSort(segment->array, segment->start, segment->end);
        mergeSort(segment->array, mid+1, segment->end);
        merge(segment->array, segment->start, mid, segment->end);
    }
    pthread_exit(NULL);
}

int main(int argc, const char * argv[])
{
    int i;
    double n, p;
    
    /* opening the input file. */
    FILE* inputFile;
    inputFile = fopen("/Users/siddharth/IITH/SEMESTER 4/OS/OS_A1/OS_A1/inp.txt", "r");
    if(inputFile == NULL)
    {
        printf("ERROR");
        exit(-1);
    }
    
    /* reading the input file. */
    fscanf(inputFile, "%lf %lf", &n, &p);
    
    /* closing the input file. */
    fclose(inputFile);
    
    int arraySize =  (int)pow(2, n), noOfSegments = (int)pow(2, p), startSegment = 0, endSegment = arraySize/noOfSegments - 1, gapSegment = arraySize/noOfSegments;
    long* array;
    array = (long*)malloc(arraySize * sizeof(long));
    
    for(i=0; i<arraySize; i++)
    {
        array[i] = rand() % 100;
    }
    
    /* opening the output file. */
    FILE* outputFile;
    outputFile = fopen("/Users/siddharth/IITH/SEMESTER 4/OS/OS_A1/OS_A1/Output.txt", "a");
    if(outputFile == NULL)
    {
        printf("ERROR");
        exit(-1);
    }
    
    /* writing the output file. */
    for(i=0; i<arraySize; i++)
    {
        fprintf(outputFile, "%ld ",array[i]);
    }
    fprintf(outputFile, "\n");
    
    struct arg* segments;
    segments = (struct arg*)malloc(noOfSegments * (sizeof(struct arg)));
    
    for(i=0; i<noOfSegments; i++)
    {
        segments[i].array = array;
        segments[i].start = startSegment;
        segments[i].end = endSegment;
        startSegment = startSegment + gapSegment;
        endSegment = endSegment + gapSegment;
    }
    
    /* clock begins. */
    clock_t begin, end, clockTimeSpent;
    begin =  clock();
    
    /* creating threads equal to number of segments. */
    pthread_t* threads;
    threads = (pthread_t*)malloc(noOfSegments * (sizeof(pthread_t)));
    for(i=0; i<noOfSegments; i++)
    {
        pthread_create(&threads[i], NULL, sortMultiThreadM1, (void*)&segments[i]);
    }
    
    /* joining the threads. */
    for(i=0; i<noOfSegments; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
    /* merging the threads. */
    for(i=0; i<noOfSegments-1; i++)
    {
        merge(array, 0, (((i + 1) * arraySize/noOfSegments) - 1) , (((i + 2) * arraySize/noOfSegments) - 1));
    }
    
    /* clock ends and the time consumed is calculated. */
    end = clock();
    clockTimeSpent = end - begin;
    unsigned long long timeSpent = 1000000*((double)clockTimeSpent/(unsigned long long)CLOCKS_PER_SEC);
    
    /* writing the output file after sorting. */
    for(i=0; i<arraySize; i++)
    {
        fprintf(outputFile, "%ld ",array[i]);
    }
    fprintf(outputFile, "\n");
    
    fprintf(outputFile, "Time Taken: %llu Microseconds\n", timeSpent);
    
    /* closing the output file. */
    fclose(outputFile);

    return 0;
}
