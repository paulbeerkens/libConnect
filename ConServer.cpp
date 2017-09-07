//
// Created by pbeerken on 8/30/17.
//

#include "ConServer.h"
#include <libLog/Logger.h>
#include <memory.h>

#include <cstring>


void ConServer::doWork()
{
    int connfd;
    pid_t childpid;

    socklen_t clilen;
    struct sockaddr_in cliaddr, serveraddr;

    if (!socket_->createSocket())
    {
        Logger::Instance().logError() << "Failed to create socket with error: " << std::strerror(errno)
                                      << LogStream::endl;
        return;
    };

    int enable = 1;
    if (!socket_->setsockopt(SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)))
    {
        Logger::Instance().logError() << "SetSocketOpt failed with error: " << std::strerror(errno) << LogStream::endl;
        return;
    }

    bzero(&serveraddr, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(9877);

    if (!socket_->bind((struct sockaddr *) &serveraddr, sizeof(serveraddr)) != 0)
    {
        Logger::Instance().logError() << "Bind failed with error: " << std::strerror(errno) << LogStream::endl;
        return;
    }

    std::cout << "Started listening on 9877" << std::endl;

    if (!socket_->listen(1024))
    {
        Logger::Instance().logError() << "Listen call failed with error: " << std::strerror(errno) << LogStream::endl;
        return;
    }


    clilen = sizeof(cliaddr);
    while (true)
    {
        ConSocket *newSocket = socket_->accept((struct sockaddr *) &cliaddr, &clilen);

    }
}