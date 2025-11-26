#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    // Set up signal handling for SIGINT
    // SIG_IGN is a macro provided by signal.h that means "ignore this signal".
    if (signal(SIGINT, SIG_IGN) == SIG_ERR) {
        perror("signal");
        return 1;
    }

    printf("Program started. Ctrl+C is now ignored.\n");
    printf("Use 'kill %d' from another terminal to stop it.\n", getpid());

    // Loop indefinitely
    while (1) {
        printf("Running... (PID: %d)\n", getpid());
        sleep(1); // Sleep for 1 second
    }

    return 0;
}

