/*The client process send two numbers and operation (+, -, *, or /) to the server process via unix socket. The server process calculate the result and return it via
same socket. The client process print the result.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/calc_socket"

struct message {
    int num1;
    int num2;
    char op;
};

void handle_client(int client_sock) {
    struct message msg;
    double result;
    if (read(client_sock, &msg, sizeof(msg)) < 0) {
        exit(EXIT_FAILURE);
    }
    switch (msg.op) {
        case '+':
            result = (double)msg.num1 + msg.num2;
            break;
        case '-':
            result = (double)msg.num1 - msg.num2;
            break;
        case '*':
            result = (double)msg.num1 * msg.num2;
            break;
        case '/':
            if (msg.num2 == 0) {
                result = 0.0;
            } else {
                result = (double)msg.num1 / msg.num2;
            }
            break;
        default:
            result = 0.0;
            break;
    }
    if (write(client_sock, &result, sizeof(result)) < 0) {
        exit(EXIT_FAILURE);
    }
    close(client_sock);
}

int main() {
    int server_sock, client_sock, len;
    struct sockaddr_un server_addr;
    unlink(SOCKET_PATH);
    if ((server_sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);
    len = sizeof(server_addr);
    if (bind(server_sock, (struct sockaddr *)&server_addr, len) == -1) {
        exit(EXIT_FAILURE);
    }
    if (listen(server_sock, 5) == -1) {
        exit(EXIT_FAILURE);
    }
    while (1) {
        if ((client_sock = accept(server_sock, NULL, NULL)) == -1) {
            continue;
        }
        handle_client(client_sock);
    }
    close(server_sock);
    return 0;
}

