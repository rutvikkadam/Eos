//Write a program that will launch two programs (e.g. who and wc). The output of ﬁrst program (e.g.who) should be given as input to second program (e.g. wc).


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int p[2];
    pipe(p);

    if (fork() == 0) {
        close(1);
        dup(p[1]);
        close(p[0]);
        close(p[1]);
        execlp("who", "who", NULL);
    }

    if (fork() == 0) {
        close(0);
        dup(p[0]);
        close(p[0]);
        close(p[1]);
        execlp("wc", "wc", NULL);
    }
    
    close(p[0]);
    close(p[1]);
    
    wait(NULL);
    wait(NULL);

    return 0;
}

