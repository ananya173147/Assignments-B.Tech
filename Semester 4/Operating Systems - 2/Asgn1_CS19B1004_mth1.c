#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>


typedef struct seg {
   long *arr;
   int start;
   int end;
} seg;


// function to look for smallest element in the given sub-array
int indexOfMinimum(long arr[], int startIndex, int n)
{
    long minValue = arr[startIndex];
    int minIndex = startIndex;

    for(int i = minIndex + 1; i < n; i++) {
        if(arr[i] < minValue){
            minIndex = i;
            minValue = arr[i];
        }
    }
    return minIndex;
}

// function to calculate x^y
long power(long x, long y)
{
	long temp;
	if(y == 0)
		return 1;
	temp = power(x, y/2);
	if ((long)y%2 == 0)
		return temp*temp;
	else{
		if(y > 0)
			return x*temp*temp;
        else
        	return (temp*temp)/x;
    	}
}

// function to initialize an array with random long values
void arr_init(long arr[],int size)
{
	for(int i=0;i<size;i++){
		arr[i] = (long)rand()*((long)rand()/10);
	}
}

// function to merge the sorted sub-arrays
void merge_sort(long arr[],long mergesort[],int start,int end)
{
	int i=0,j=start,k=0;
        while(i<start && j<end){
            if(arr[i] < arr[j]){
               	mergesort[k] = arr[i];
               	i++;
           	}
           	else{
               	mergesort[k] = arr[j];
               	j++;
           	}
           	k++;
        }

        if (i>=start){
            while (j<end){
               	mergesort[k] = arr[j];
               	j++;
               	k++;
            }
        }

        if (j>=end){
            while (i<start){
               	mergesort[k] = arr[i];
               	i++;
               	k++;
            }
        }
}


// function to sort each segment using threads using selection sort
void *seg_sort(void* arg)
{
	int i,j;
    long temp;
	seg* a = (seg*) arg;
	for(i=a->start; i<a->end; i++){
        int index = indexOfMinimum(a->arr,i,a->end);
        temp = a->arr[i];
        a->arr[i] = a->arr[index];
        a->arr[index] = temp;
    }

    pthread_exit(NULL);
}

int main(){

// taking input from "inp.txt"
FILE *fp;
int n,p,i,j;
fp = fopen("inp.txt","r");

if(!fp){
	printf("NO FILE");
	return 1;
}

fscanf(fp,"%d %d", &n, &p);
fclose(fp);

int arr_size = power(2,n);
long *array;
array = malloc(sizeof(long)*arr_size);
arr_init(array,arr_size);

// printing array after initializing it
FILE *f1 = fopen("output.txt", "w");
if(f1){
    for(i=0;i<arr_size;i++)
    fprintf(f1, "%ld ", array[i]);
    fprintf(f1, "\n");
    fclose(f1);
}
else{
    printf("Error!");
    return 1;
}

int no_threads = power(2,p);
int start_s = 0;
long end_s = power(2,n-p);
long incre = power(2,n-p);

// declaring an array of structures, seg* segments, and initializing it with appropriate values
seg* segments;
segments = (seg*)malloc(no_threads*sizeof(seg));
long *mergesort;
mergesort = malloc(sizeof(long)*(arr_size));

for(i=0; i<no_threads; i++){
    segments[i].arr = array;
    segments[i].start = start_s;
    segments[i].end = end_s;
    start_s += incre;
    end_s += incre;
}

// we create 2^p threads
pthread_t* threads;
threads = (pthread_t*)malloc(no_threads*sizeof(pthread_t));

// note the time when computation begins
clock_t begin = clock();

// creating threads and passing the data for sorting of one segment at a time.
for(i=0; i<no_threads; i++){
    pthread_create(&threads[i], NULL, seg_sort, (void*)(&segments[i]));
}

for(i=0; i<no_threads; i++){
    pthread_join(threads[i], NULL);
}


for(i=0; i<no_threads-1; i++){
    merge_sort(array,mergesort,incre,incre+power(2,n-p));
    for(j=0;j<incre+power(2,n-p);j++){
        array[j] = mergesort[j];
    }
    incre += power(2,n-p);
}

// note the time when computation ends
clock_t end = clock();
clock_t clockTimeSpent = end - begin;
unsigned long long time_spent = 1000000*((double)clockTimeSpent/(unsigned long long)CLOCKS_PER_SEC);

free(mergesort);

// printing array after sorting it and the time taken for computation
FILE *f2 = fopen("output.txt", "a");
if(f2){
    for(i=0;i<arr_size;i++)
    fprintf(f2, "%ld ", array[i]);
    fprintf(f2, "\n");
    //if(array[i]>array[i+1])
    //printf("%ld %ld\n", array[i],array[i+1]);
    fprintf(f2, "Time taken: %llu Microseconds\n",time_spent);
    fclose(f2);
}
else{
    printf("Error!");
    return 1;
}

free(array);
free(segments);
return 0;
}
