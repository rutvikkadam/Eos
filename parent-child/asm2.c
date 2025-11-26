/*From a parent process (A) create a child process (B). The child (B) in turn creates new child process (C) and it (C) in turn create new child (D). All these processes should run concurrently for 5 seconds and cleaned up properly upon termination.*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int s, s1, s2;
	printf("Program started !!!\n");
	printf("Parent(A) : ppid = %d\n",getppid());
	int ret = fork();
	if(ret == 0)
	{
		printf("Child(B) : pid = %d\n",getpid());
		int ret1 = fork();
		if(ret1 == 0)
		{
			printf("child(C) : pid = %d\n",getpid());
			int ret2 = fork();
			if(ret2 == 0)
			{
				for(int i=1; i<=3; i++)
					printf("child (D) : pid = %d\n",getpid());
				sleep(5);
			}
			else
			{
				for(int i=1; i<=3; i++)
				{
					printf("child (C) : = %d\n",i);
					sleep(5);
				}
				waitpid(ret2, &s2, 0);
			}
		}  
		else
		{
			for(int i=1; i<=3; i++)
			{
				printf("child (B) : = %d\n",i);
				sleep(5);
			}
			waitpid(ret1, &s1, 0);
		}
	}
	else
	{
		for(int i=1; i<=3; i++)
		{
			printf("Parent : = %d\n", i);
			sleep(5);
		}
		waitpid(ret, &s, 0);
	}
	
	printf("Program finished !!\n");
	return 0;
}


