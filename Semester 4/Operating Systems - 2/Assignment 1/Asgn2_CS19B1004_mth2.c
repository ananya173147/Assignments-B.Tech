#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

// structure that will keep track of the starting and ending points of each segment of the array while having access to the array
typedef struct seg {
long *arr;
long *mergesort;
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
	if ((int)y%2 == 0)
		return temp*temp;
	else{
		if(y > 0)
			return x*temp*temp;
        else
        	return (temp*temp)/x;
    	}
}

// function to initialize an array with random int values
void arr_init(long arr[],int size)
{
	for(int i=0;i<size;i++){
		arr[i] = (long)rand()*(long)rand()/10;
	}
}

// function to merge the sorted sub-arrays
void *merge_sort(void* arg)
{
  seg* a = (seg*) arg;
  int end1 = a->end;
  int end2 = a->end + (a->end-a->start);
	int i=a->start,j=end1,k=a->start;
        while (i<end1 && j<end2){
            if(a->arr[i] < a->arr[j]){
                a->mergesort[k] = a->arr[i];
                i++;
            }
            else{
                a->mergesort[k] = a->arr[j];
                j++;
            }
            k++;
        }

        if (i>=end1){
            while (j<end2){
                a->mergesort[k] = a->arr[j];
                j++;
                k++;
            }
        }

        if (j>=end2){
            while (i<end1){
                a->mergesort[k] = a->arr[i];
                i++;
                k++;
            }
        }

  for(i=a->start;i<end2;i++)
    a->arr[i] = a->mergesort[i];

  a->end = a->end + (a->end-a->start);
  pthread_exit(NULL);
}


// function to sort each segment using threads
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
print(array,arr_size);

int no_threads = power(2,p);
int start_s = 0;
long end_s = power(2,n-p);
long incre = power(2,n-p);

seg* segments;
segments = (seg*)malloc(no_threads*sizeof(seg));
long *mergesort;
mergesort = malloc(sizeof(long)*(arr_size));

for(i=0; i<no_threads; i++){
 	segments[i].arr = array;
    segments[i].mergesort = mergesort;
 	segments[i].start = start_s;
 	segments[i].end = end_s;
 	start_s += incre;
 	end_s += incre;
}

// we create 2^p threads
pthread_t* threads;
threads = (pthread_t*)malloc(no_threads*sizeof(pthread_t));

// creating threads and passing the data for sorting of one segment at a time.
for(i=0; i<no_threads; i++){
	pthread_create(&threads[i], NULL, seg_sort, (void*)(&segments[i]));
}

// note the time when computation begins
clock_t begin = clock();

for(i=0; i<no_threads; i++){
        pthread_join(threads[i], NULL);
}

int no_segments = no_threads/2;
int k = 2;

// loop till all the segments are merged, i.e, till we are left with only one sorted segment which is the final sorted array.
while(no_segments>=1){
  //create half the number of threads as the number of segments
  pthread_t* threads;
  threads = (pthread_t*)malloc((no_segments)*sizeof(pthread_t));

  //assigning threads the right segments to sort and merge
  for(i=0; i<no_segments; i++){
	  pthread_create(&threads[i], NULL, merge_sort,(void*)(&segments[k*i]));
  }

  //wait for the threads to terminate
  for(i=0; i<no_segments; i++){
        pthread_join(threads[i], NULL);
  }

  //after the threads merge the segments, the number of segments becomes half
  no_segments = no_segments/2;
  k = k*2;
}
// note the time when computation ends
clock_t end = clock();
clock_t clockTimeSpent = end - begin;
unsigned long long time_spent = 1000000*((double)clockTimeSpent/(unsigned long long)CLOCKS_PER_SEC);

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
