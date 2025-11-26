/*Execute the INET server-client chat application on two different computers in a network.*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_IP "192.168.1.28"
#define SERV_PORT 2809

int main()
{
    int serv_fd, cli_fd, ret;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clisock_len = sizeof(cli_addr);
    char msg[512];

    // create main socket
    serv_fd = socket(AF_INET, SOCK_STREAM, 0);
    // bind socket address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);
    serv_addr.sin_port = htons(SERV_PORT);
    ret = bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    // listen main socket
    listen(serv_fd, 5);
    // accept client connection
    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_fd = accept(serv_fd, (struct sockaddr *)&cli_addr, &clisock_len);
    do
    {
        // accept string from client
        read(cli_fd, msg, sizeof(msg));
        // display that string to user
        printf("client> %s", msg);
        // input a string from user
        printf("server> ");
        fgets(msg, sizeof(msg), stdin);
        // send string to client
        write(cli_fd, msg, strlen(msg) + 1);
    } while (strcmp(msg, "bye\n") != 0);
    // repeat commn until "bye\n"

    // close comm socket
    close(cli_fd);
    // close main socket
    shutdown(serv_fd, SHUT_RDWR);
    return 0;
}
