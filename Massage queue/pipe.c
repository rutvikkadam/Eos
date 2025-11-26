//Write a program to ﬁnd the size of the pipe buﬀer.


#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(void) {
    int fds[2];
    
    if (pipe(fds) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
    
    int size = fcntl(fds[0], F_GETPIPE_SZ, 0);
    if (size == -1) {
        if (errno == EINVAL) {
            fprintf(stderr, "F_GETPIPE_SZ not supported on this kernel.\n");
        } else {
            perror("fcntl failed to get pipe size");
        }
        close(fds[0]);
        close(fds[1]);
        exit(EXIT_FAILURE);
    }
    
    printf("The size of the pipe buffer is %d bytes.\n", size);
    
    close(fds[0]);
    close(fds[1]);
    
    return 0;
}

