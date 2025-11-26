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

int main() {
    int client_sock, len;
    struct sockaddr_un server_addr;
    struct message msg;
    double result;
    if ((client_sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);
    len = sizeof(server_addr);
    if (connect(client_sock, (struct sockaddr *)&server_addr, len) == -1) {
        exit(EXIT_FAILURE);
    }
    printf("Enter number: ");
    scanf("%d", &msg.num1);
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &msg.op);
    printf("Enter number: ");
    scanf("%d", &msg.num2);
    if (write(client_sock, &msg, sizeof(msg)) < 0) {
        exit(EXIT_FAILURE);
    }
    if (read(client_sock, &result, sizeof(result)) < 0) {
        exit(EXIT_FAILURE);
    }
    printf("Result: %.2f\n", result);
    close(client_sock);
    return 0;
}

