#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#define BUFFER_SIZE 10
#define IO 2

int main () {

  int fd;
  int *bptr;
  int fd1;
  int *io;
  /* Open the Shared Buffer for reading by Consumer */
  fd = shm_open("/myBuffer", O_RDONLY, 0666);
  
  fd1 = shm_open("/myBufferio", O_RDWR, 0666);
  
  if (fd == -1||fd1 == -1)
    {  /* Handle error */;
    printf("No Shared Buffer Exists\n");
    return -1;
    }

  /* Map shared memory object to process’ address space */
  bptr = mmap(NULL, sizeof(int)*BUFFER_SIZE, PROT_READ, MAP_SHARED, fd, 0);
  if (bptr == MAP_FAILED)
    {
      printf("Error in mapping Shared Buffer\n");
      return -1;
    }
  io = mmap(NULL, sizeof(int)*IO, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
  if (io == MAP_FAILED)
    {
      printf("Error in mapping Shared Buffer\n");
      return -1;
    }
  
/* Now we can refer to mapped region using fields of bptr */
/*
  for(int i=0; i<BUFFER_SIZE; i++)
    {
     //write to shared memory by producer
      bptr[i]=i*i;
    }
*/
printf("Consumer with PID=%d is reading from Shared Buffer\n",getpid());

int next_consumed; 

//printf("%d %d\n",inout[0],inout[1]);
while (1) {

while (io[0] == io[1]);
next_consumed = bptr[io[1]]; 
printf("%dth item in the Shared Buffer:%d\n", io[1], bptr[io[1]]); 
io[1] = (io[1] + 1) % BUFFER_SIZE;
/* consume the item in next consumed */ 
} 
  
 /* for(int i=0; i<BUFFER_SIZE; i++)
    {
      //Reading 
      printf("%dth item in the Shared Buffer:%d\n", i, bptr[i]); 
    }
  */
  //shm_unlink("/myBuffer");
  return 0;
}
