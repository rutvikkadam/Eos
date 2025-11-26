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
    int cli_fd, ret;
    struct sockaddr_in serv_addr;
    char msg[512];
    // create a new socket
    cli_fd = socket(AF_INET, SOCK_STREAM, 0);
    // connect to server socket
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);
    serv_addr.sin_port = htons(SERV_PORT);
    ret = connect(cli_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    do
    {
        // input a string from user
        printf("client> ");
        fgets(msg, sizeof(msg), stdin);
        // send string to server
        write(cli_fd, msg, strlen(msg) + 1);
        // accept string from server
        read(cli_fd, msg, sizeof(msg));
        // display that string to user
        printf("server> %s", msg);
    } while (strcmp(msg, "bye\n") != 0);
    // repeat commn until "bye\n"

    // close client
    close(cli_fd);
    return 0;
}
