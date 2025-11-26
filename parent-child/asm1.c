/*From one parent create 5 child processes. Each child should run for 5 seconds and print count along with its pid. Parent should wait for all child processes to complete and clean all of them. Hint: use loop to fork() multiple child processes.*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(void)
{
	int s,ret;
	printf("Program started !!!\n");

	for(int i=0; i<5; i++)
	{
		int ret=fork();
		if(ret == 0)
		{
			printf("parent: ppid = %d\n", getppid());
			printf("child %d :pid = %d\n",i,getpid());
			sleep(5);
			exit(0);
		}
	}
	printf("Parent : All 5 childs are created !!!\n");
	for(int i=0; i<5; i++)
	{
		ret= wait(&s);//The wait() system call suspends execution of the calling thread until one of its children terminates.wait(): on success, returns the process ID of the terminated child; on failure, -1 is returned.	

	printf("Parent : Exit status of child %d =%d\n",ret, WEXITSTATUS(s));//returns the exit status of the child.
	}
	printf("Program fininshed !!!\n");
	return 0;
}

