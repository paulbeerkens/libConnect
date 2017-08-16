//
// Created by pbeerken on 6/8/17.
//

#ifndef LIBCONNECT_CONTCPRECEIVER_H
#define LIBCONNECT_CONTCPRECEIVER_H

#include "ConThread.h"
#include "ConConnectionCallback.h"
#include <libUtils/MutexWithOwnersip.h>

class ConTCPReceiver : public ConRunnable
{
public:
    ConTCPReceiver(const std::string &host, int port, IConnectionCallback *callback)
            : remoteHost_(host), remotePort_(port), callback_(callback)
    {
    }

    void doWork() override;

protected:
    bool connect();

    bool disconnect();

    bool disconnectNoLocking();

    bool readAMessage();

    bool readNBytes(void *buf, int32_t len);

    IConnectionCallback *callback_ = nullptr;

    const std::string remoteHost_;
    int remotePort_;
    bool connected_ = false;
    int socketfd_ = -1;

    MutexWithOwnership mutex_;
};


#endif //LIBCONNECT_CONTCPRECEIVER_H
