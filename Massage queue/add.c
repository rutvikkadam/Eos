/*The child process send two numbers to the parent process via message queue. The parent process calculate the sum and return via same message queue. The child process print the result and exit.The parent process wait for completion of the child and then exit.*/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define MSG_KEY 0x1234

struct msgbuf{
	long mtype;
	int mtext[2];
};

int main(void)
{
	int msgid = msgget(MSG_KEY, IPC_CREAT | 0600);
	if(msgid == -1)
	{
		perror("msgget() is failed");
		_exit(-1);
	}

	int pid = fork();
	if(pid == 0)
	{
		// child process - writer
		struct msgbuf m1;
		m1.mtype = 10;
		for(int i=0; i<2; i++)
		{
		printf("child : Enter number[i] : ");
		scanf("%d",m1.mtext[i]);
		}
		int ret = msgsnd(msgid, &m1, sizeof(m1.mtext), 0);
		if(ret == -1)
		{
			perror("msgsnd() is failed");
			_exit(-1);
		}
		printf("child : MSG is sent successfully !!!\n");
	}
	else
	{
		// parent process - reader
		printf("parent : waiting for message ....\n");
		struct msgbuf m2;
		int ret = msgrcv(msgid, &m2, sizeof(m2.mtext), 10, 0);
		if(ret == -1)
		{
			perror("msgrcv() is failed");
			_exit(-1);
		}
		for(int i=0; i<2; i++)
		{
		int temp=0;
		printf("parent : Received number = %d\n", m2.mtext[i]);
		temp= temp+m2.mtext[i];
		printf("Addition is : %d\n",temp);
		}
		int s;
		waitpid(pid, &s, 0);
		// 4. remove/delete msg que from memory 
		msgctl(msgid, IPC_RMID, NULL);
	}

	return 0;
}

