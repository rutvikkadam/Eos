#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

// Function prototype for the signal handler
void handle_sigchld(int sig);

int main() {
    // 1. Set up the SIGCHLD handler to prevent zombies
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigchld;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    
    if (sigaction(SIGCHLD, &sa, 0) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Shell started. Type 'background_command &' to test.\n");
    
    // Simplified shell loop (main process)
    while (1) {
        printf("\nosh> ");
        char input[100];
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        // Remove newline character
        input[strcspn(input, "\n")] = 0;

        // Check if command ends with '&' (very simple parsing for demo)
        int background = (strlen(input) > 0 && input[strlen(input) - 1] == '&');

        // --- Core Shell Logic Simulation ---
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
        } else if (pid == 0) {
            // Child process: Execute the command (here we simulate work)
            printf("[Child %d] Running command...\n", getpid());
            sleep(background ? 3 : 1); // Background tasks "sleep" longer
            printf("[Child %d] Command finished.\n", getpid());
            exit(EXIT_SUCCESS); // Child terminates here
        } else {
            // Parent process
            if (background) {
                printf("[Parent] Forked background child %d. Not waiting.\n", pid);
            } else {
                printf("[Parent] Forked foreground child %d. Waiting...\n", pid);
                // For foreground processes, you must wait:
                waitpid(pid, NULL, 0);
                printf("[Parent] Foreground child %d reaped immediately.\n", pid);
            }
        }
    }

    return 0;
}

/**
 * SIGCHLD Signal Handler
 * This function runs asynchronously whenever a child process terminates.
 * It calls waitpid() repeatedly to clean up all terminated children (reap zombies).
 */
void handle_sigchld(int sig) {
    pid_t pid;
    int status;
    
    // Use WNOHANG to return immediately if no child has exited.
    // Use a while loop to reap all children that might have exited simultaneously.
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("\n[Handler] Reaped background child %d asynchronously.\nosh> ", pid);
        fflush(stdout); // Ensure output appears correctly after a signal
    }
}

