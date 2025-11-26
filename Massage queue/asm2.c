//The child process send two numbers to the parent process via pipe. The parent process calculate the sum and return via another pipe. The child process print the result and exit. The parent process wait for completion of the child and then exit.


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {
    int c2p[2], p2c[2];

    if (pipe(c2p) == -1 || pipe(p2c) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        int n[2], s;
        close(c2p[0]);
        close(p2c[1]);

        printf("child: Enter two numbers: ");
        scanf("%d %d", &n[0], &n[1]);

        write(c2p[1], n, sizeof(n));
        close(c2p[1]);

        read(p2c[0], &s, sizeof(s));
        close(p2c[0]);

        printf("child: Received sum = %d\n", s);
        exit(EXIT_SUCCESS);
    } else {
        int n[2], s;
        close(c2p[1]);
        close(p2c[0]);

        printf("parent: Waiting for numbers from child...\n");

        read(c2p[0], n, sizeof(n));
        close(c2p[0]);

        printf("parent: Received numbers %d and %d\n", n[0], n[1]);

        s = n[0] + n[1];
        
        write(p2c[1], &s, sizeof(s));
        close(p2c[1]);

        waitpid(pid, NULL, 0);

        printf("parent: Child process finished, exiting.\n");
    }

    return 0;
}

