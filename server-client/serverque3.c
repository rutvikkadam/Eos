/*The client process send two numbers and operation (+, -, *, or /) to the server process via inet socket. The server process calculate the result and return it via
same socket. The client process print the result.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

struct message {
    int num1;
    int num2;
    char op;
};

void handle_client(int client_sock) {
    struct message msg;
    double result;
    if (read(client_sock, &msg, sizeof(msg)) <= 0) {
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
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        exit(EXIT_FAILURE);
    }
    if (listen(server_sock, 5) < 0) {
        exit(EXIT_FAILURE);
    }
    while (1) {
        addr_size = sizeof(client_addr);
        if ((client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size)) < 0) {
            continue;
        }
        handle_client(client_sock);
    }
    close(server_sock);
    return 0;
}

