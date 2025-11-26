/*Create message queue to send the fifo name and file name from client to server. Send given file to the client via the given fifo. Client should accept that file and save to disk.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_BASE_PATH "/tmp/client_fifo_"
#define BUF_SIZE 4096

struct message {
    long type;
    pid_t client_pid;
    char filename[256];
};

int main() {
    key_t key;
    int msgid;
    struct message msg;
    char fifo_path[256];
    char buffer[BUF_SIZE];
    int file_fd, fifo_fd;
    ssize_t bytes_read;

    key = ftok(".", 'a');
    msgid = msgget(key, 0666 | IPC_CREAT);

    while (1) {
        msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 1, 0);

        sprintf(fifo_path, "%s%d", FIFO_BASE_PATH, msg.client_pid);

        file_fd = open(msg.filename, O_RDONLY);
        if (file_fd < 0) {
            continue;
        }

        fifo_fd = open(fifo_path, O_WRONLY);
        if (fifo_fd < 0) {
            close(file_fd);
            continue;
        }

        while ((bytes_read = read(file_fd, buffer, BUF_SIZE)) > 0) {
            write(fifo_fd, buffer, bytes_read);
        }

        close(file_fd);
        close(fifo_fd);
    }
    return 0;
}

