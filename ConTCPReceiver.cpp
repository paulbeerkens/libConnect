//
// Created by pbeerken on 6/8/17.
//

#include "ConTCPReceiver.h"
//#include <thread>
//#include <chrono>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libLog/Logger.h>

void ConTCPReceiver::doWork()
{
    while (!requestedToTerminate_)
    {
        while (!requestedToTerminate_ && !connected_)
        {
            if (!connect())
            {//if not successfully connected wait and try again
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        while (connected_)
        {
            //read message
        }
    }

}

bool ConTCPReceiver::connect()
{
    Logger::Instance().logInfo() << "Trying to connect" << LogStream::endl;
    socketfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd_ < 0)
    {
        Logger::Instance().logInfo() << "Failed to create a second" << LogStream::endl;
        return false;
    };

    struct sockaddr_in serveraddr;

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(remotePort_);
    if (inet_pton(AF_INET, remoteHost_.c_str(), &serveraddr.sin_addr) != 1)
    {
        //log error
        return false;
    }


    if (::connect(socketfd_, (const sockaddr *) &serveraddr, sizeof(serveraddr)) != 0)
    {
        //log error
        return false;
    }

    if (callback_ != nullptr)
    {
        callback_->onConnected();
    }

    connected_ = true;
    return connected_;
}