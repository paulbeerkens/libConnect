//
// Created by pbeerken on 6/8/17.
//

#ifndef LIBCONNECT_CONTCPRECEIVER_H
#define LIBCONNECT_CONTCPRECEIVER_H

#include "ConThread.h"
#include "ConCallback.h"
#include <libUtils/MutexWithOwnersip.h>
#include "ConSocket.h"
#include <memory>

class ConTCPReceiver : public ConRunnable
{
public:
    ConTCPReceiver(const std::string &host, int port, IConnectionCallback *callback,
                   std::unique_ptr<ConSocket> socket = std::make_unique<ConSocketImpl>())
            : remoteHost_(host), remotePort_(port), callback_(callback), socket_(std::move(socket))
    {
        assert (callback_);
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

    MutexWithOwnership mutex_;
    std::unique_ptr<ConSocket> socket_ = nullptr;
};


#endif //LIBCONNECT_CONTCPRECEIVER_H
