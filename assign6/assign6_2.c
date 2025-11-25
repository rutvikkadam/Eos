#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

/**
 * Executes a single command using fork() and execvp().
 * @param argv_list An array of strings representing the command and its arguments.
 */
void run_command(char *argv_list[]) {
    pid_t pid = fork();

    if (pid == -1) {
        // Error handling for fork failure
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process: execute the command
        printf("Child process %d: Executing command: %s %s\n", getpid(), argv_list[0], argv_list[2]);
        execvp(argv_list[0], argv_list);

        // If execvp returns, an error occurred
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }
    // Parent process continues its loop to create other children concurrently
}

int main() {
    // Array of compilation commands to run concurrently
    char *compile_cmds[][4] = {
        {"gcc", "-c", "circle.c", NULL},
        {"gcc", "-c", "square.c", NULL},
        {"gcc", "-c", "rectangle.c", NULL},
        {"gcc", "-c", "main.c", NULL}
    };
    int num_compilations = sizeof(compile_cmds) / sizeof(compile_cmds[0]);
    int status;
    pid_t wpid;

    printf("Starting concurrent compilation of object files...\n");

    // Create child processes for all compilations
    for (int i = 0; i < num_compilations; i++) {
        run_command(compile_cmds[i]);
    }

    // Parent process waits for all child processes to finish
    // This prevents the parent from linking before all object files are ready.
    printf("\nParent process %d: Waiting for all child processes to complete...\n", getpid());
    while ((wpid = wait(&status)) > 0) {
        if (WIFEXITED(status)) {
            printf("Parent process %d: Child %d finished with exit status %d.\n", getpid(), wpid, WEXITSTATUS(status));
        } else {
            printf("Parent process %d: Child %d terminated abnormally.\n", getpid(), wpid);
        }
    }

    // After all children are done, proceed to the linking phase
    printf("\nAll object files compiled. Starting linking phase...\n");
    char *link_cmd[] = {"gcc", "-o", "program.out", "circle.o", "square.o", "rectangle.o", "main.o", NULL};
    
    // Execute linking command using fork and execvp
    pid_t link_pid = fork();
    if (link_pid == -1) {
        perror("fork failed for linking");
        return EXIT_FAILURE;
    } else if (link_pid == 0) {
        printf("Child process %d: Executing linking command...\n", getpid());
        execvp(link_cmd[0], link_cmd);
        perror("execvp failed for linking");
        exit(EXIT_FAILURE);
    } else {
        // Parent waits for the linker child process to finish
        waitpid(link_pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            printf("\nLinking successful. Executable 'program.out' created.\n");
            printf("You can now run the program using: ./program.out\n");
        } else {
            fprintf(stderr, "\nLinking failed.\n");
        }
    }

    return EXIT_SUCCESS;
}

