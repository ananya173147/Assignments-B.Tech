#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
int status = 0;
pid_t pid,pid2;
pid = fork();
printf("Forking completed\n");
if(pid<0){
	fprintf(stderr,"Fork Failed");
	return 1;
}
else if(pid==0){ //Child process runs when pid=0
	while(1){
		printf("This is child 1 with pid %d\n",pid);
		sleep(1);
	}
}
else{ //Parent process when pid>0
	pid2 = fork(); //Forking parent process to create another child
	
	if(pid2<0){ 
		fprintf(stderr,"Fork Failed");
		return 1;
	}
	else if(pid2==0){ //Child 2 process with pid 0
		sleep(10);		
		printf("This is child 2 with pid %d, woke up\n",pid2);
		kill(pid,SIGKILL);	//killing child 1 associated with pid
		printf("This is child 2 with pid %d after killing child 1\n",pid2);
		printf("Sleeping for 10 sec...\n");
		sleep(10);
		printf("Child 2 exiting... pid = %d\n",pid2);
		exit(0); //child 2 terminating
	}	
	else{
		waitpid(-1,&status,0); //waiting for child process to change state
	}
	waitpid(-1,&status,0);	//waiting for child process to change state
	
	printf("Child processes are completed. This is the parent process - pid %d\n",pid); //Parent process exiting after child processes have terminated
	
}

return 0;
}
