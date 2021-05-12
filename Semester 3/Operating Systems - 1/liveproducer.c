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
  int next; 	
  /* Create shared memory object and set its size */
  fd = shm_open("/myBuffer", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  fd1 = shm_open("/myBufferio", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  
  if (fd == -1 || fd1 == -1)
    {  /* Handle error */;
    printf("Error in creating Shared Buffer\n");
    return -1;
    }

  if (ftruncate(fd, sizeof(int)*BUFFER_SIZE) == -1) //set Size
    {
      printf("Error in setting the size of Shared Buffer\n"); /* Handle error */
      return -1;
    }
    
  if (ftruncate(fd1, sizeof(int)*IO) == -1) //set Size
    {
      printf("Error in setting the size of Shared Buffer\n"); /* Handle error */
      return -1;
    }
    
    /* Map shared memory object to process’ address space */ 
  bptr = mmap(NULL, sizeof(int)*BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
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


while (1) { 

 while ( ((io[0] + 1) % BUFFER_SIZE) == io[1] ) ;
 printf("Enter the item to be placed in %d slot: ",io[0]);
 scanf("%d",&next); 
 bptr[io[0]] = next;
 //printf("%d has been stored and next is %d\n",bptr[io[0]],next);
 io[0] = (io[0] + 1) % BUFFER_SIZE; 
 //printf("Updated in is %d\n", io[0]);
}


  return 0;
}
