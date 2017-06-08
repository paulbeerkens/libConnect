//
// Created by pbeerken on 6/8/17.
//

#include <string>
#include <iostream>

#include <sys/socket.h>

#include    <netinet/in.h>
#include <memory.h>
#include <cstring>

#include    <arpa/inet.h>    /* inet(3) functions */

#include    <unistd.h>

void
str_echo(int sockfd)
{
    ssize_t n;
    char buffer[10000];

    again:
    while ((n = read(sockfd, buffer, 10000)) > 0)
    {
        std::cout << "Received " << n << " " << std::string(buffer, n) << std::endl;
    }
    if (n < 0 && errno == EINTR)
    {
        goto again;
    } else if (n < 0)
    {
        std::cout << "read error" << std::endl;
    }
}

int
main(int argc, char **argv)
{
    int listenfd, connfd;
    pid_t childpid;

    socklen_t clilen;
    struct sockaddr_in cliaddr, serveraddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serveraddr, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(9877);

    if (bind(listenfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) != 0)
    {
        std::cout << "Bind failed with error: " << std::strerror(errno);
        return 1;
    }

    listen(listenfd, 1024);

    while (true)
    {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
        if ((childpid = fork()) == 0)
        {
            close(listenfd);
            str_echo(connfd);
        }
        close(connfd);
    }

    return 0;
}

