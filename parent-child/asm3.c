/*Find max number of child processes that can be created on Linux using C program? Hint: use fork() in
inﬁnite loop (wisely).*/


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
    unsigned long count = 0;
    while (1) {
        if (fork() == 0) {
            exit(0);
        }
        count++;
        if (errno) {
            if (errno == EAGAIN) {
                printf("%lu\n", count - 1);
            }
            break;
        }
    }
    while (wait(NULL) > 0);
    return 0;
}

