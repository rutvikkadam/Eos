#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t pid1, pid2, pid3, pid4, pid5, pid6;
	int status, success = 1;

	pid1 = fork();// create child process
	if (pid1 == 0) /*On success, the PID of the child process is returned in the parent, and 0 is returned in the child.On  failure, -1 is returned in the parent, no child process is created, and errno is set to indicate the error.*/
        {
		char *cmd[] = {"gcc", "-c", "circle.c", NULL};
		execvp(cmd[0], cmd);//functions replaces the current process image with a new process image.
		exit(1);
	}

	pid2 = fork();
	if (pid2 == 0) {
		char *cmd[] = {"gcc", "-c", "square.c", NULL};
		execvp(cmd[0], cmd);
		exit(1);
	}

	pid3 = fork();
	if (pid3 == 0) {
		char *cmd[] = {"gcc", "-c", "rectangle.c", NULL};
		execvp(cmd[0], cmd);
		exit(1);
	}

	pid4 = fork();
	if (pid4 == 0) {
		char *cmd[] = {"gcc", "-c", "main.c", NULL};
		execvp(cmd[0], cmd);
		exit(1);
	}

	waitpid(pid1, &status, 0);
	if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0)) success = 0;

	waitpid(pid2, &status, 0);
	if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0)) success = 0;

	waitpid(pid3, &status, 0);
	if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0)) success = 0;

	waitpid(pid4, &status, 0);
	if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0)) success = 0;

	if (!success) {
		printf("Compilation failed\n");
		return 1;
	}

	pid5 = fork();
	if (pid5 == 0) {
		char *link_cmd[] = {"gcc", "-o", "program.out", "circle.o", "square.o", "rectangle.o", "main.o", NULL};
		execvp(link_cmd[0], link_cmd);
		exit(1);
	}
	waitpid(pid5, &status, 0);
	if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0)) {
		printf("Linking failed\n");
		return 1;
	}

	pid6 = fork();
	if (pid6 == 0) {
		char *run_cmd[] = {"./program.out", NULL};
		execvp(run_cmd[0], run_cmd);
		exit(1);
	}
	waitpid(pid6, &status, 0);
	if (WIFEXITED(status))
		printf("Program exited with status %d\n", WEXITSTATUS(status));

	return 0;
}

