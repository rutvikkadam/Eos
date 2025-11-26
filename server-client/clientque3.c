/*The client process send two numbers and operation (+, -, *, or /) to the server process via inet socket. The server process calculate the result and return it via
same socket. The client process print the result.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define IP "127.0.0.1"

struct message {
    int num1;
    int num2;
    char op;
};

int main() {
    int client_sock;
    struct sockaddr_in server_addr;
    struct message msg;
    double result;
    if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &server_addr.sin_addr);
    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
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

