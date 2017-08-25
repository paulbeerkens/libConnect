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
                disconnect();
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        while (!requestedToTerminate_ && connected_)
        {
            if (!readAMessage())
            {
                disconnect();
            }
        }
    }

}

bool ConTCPReceiver::connect()
{
    std::lock_guard<std::mutex> guard(mutex_);
    assert (!socket_->isSocketSet()); //should not call connect it already a socket in use
    if (socket_->isSocketSet())
    {
        disconnectNoLocking();
    }

    if (!socket_->createSocket())
    {
        Logger::Instance().logError() << "Failed to create a socket" << LogStream::endl;
        return false;
    };

    struct sockaddr_in serveraddr;

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(remotePort_);
    if (inet_pton(AF_INET, remoteHost_.c_str(), &serveraddr.sin_addr) != 1)
    {
        Logger::Instance().logError() << "Failed to convert ip address: " << remoteHost_ << LogStream::endl;
        return false;
    }

    if (!socket_->connect((const sockaddr *) &serveraddr, sizeof(serveraddr)))
    {
        Logger::Instance().logError() << "Connect failed to : " << remoteHost_ << ":" << remotePort_ << LogStream::endl;
        return false;
    }

    if (callback_ != nullptr)
    {
        callback_->onConnected();
    }

    connected_ = true;
    return connected_;
}

bool ConTCPReceiver::disconnect()
{
    assert (!mutex_.owned()); //should call disconnectNoLocking if the mutex is already owned
    std::lock_guard<MutexWithOwnership> guard(mutex_);
    return disconnectNoLocking();
}

bool ConTCPReceiver::disconnectNoLocking()
{
    assert (mutex_.owned());
    if (socket_->isSocketSet())
    {
        socket_->destroySocket();
        connected_ = false;
    }
}

int MAX_MSG_LENGTH = 10 * 1024;

bool
ConTCPReceiver::readAMessage()
{
    int32_t len;
    if (!readNBytes(&len, sizeof(len)))
    {
        Logger::Instance().logError() << "Failed to read length. Disconnecting now." << LogStream::endl;
        return false;
    }

    if (len > MAX_MSG_LENGTH)
    {
        Logger::Instance().logError() << "Received invalid length of " << len << ". Disconnecting now."
                                      << LogStream::endl;
        return false;
    }

    char buffer[MAX_MSG_LENGTH + 1];

    if (!readNBytes(&buffer, len))
    {
        Logger::Instance().logError() << "Failed to read message. Disconnecting now." << LogStream::endl;
        return false;
    }

    //std::string s(buffer, len - 1);
    //Logger::Instance().logError() << "Received: " << s << LogStream::endl;
    if (callback_)
    {
        callback_->onMsg(&buffer, len);
    }

    return true;
}


bool ConTCPReceiver::readNBytes(void *buf, int32_t len)
{
    assert (len > 0);
    assert (connected_);
    //   assert (socket_->isSocketSet());

    char *writePtr = static_cast <char *> (buf);
    int32_t bytesToRead = len;

    //int testValue;
    //int s=socket_->test (&testValue);


    while ((bytesToRead > 0) && connected_)
    {
        int32_t bytesRead = socket_->read(writePtr, bytesToRead);
        if (bytesRead > 0)
        {
            bytesToRead -= bytesRead;
            writePtr += bytesRead;
        } else
        {
            if (errno != EINTR)
            {
                disconnect();
                return false;
            }
        }

    };
    return true;
}


