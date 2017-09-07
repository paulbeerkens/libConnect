//
// Created by pbeerken on 8/30/17.
//

#ifndef LIBCONNECT_CONSERVER_H
#define LIBCONNECT_CONSERVER_H

#include <string>
#include "ConCallback.h"
#include "ConSocket.h"
#include "ConThread.h"


class ConServer : public ConRunnable
{
public:
    ConServer(const std::string &host, int port, IServerCallback *callback,
              ConSocket *socket = new ConSocketImpl())
            : remoteHost_(host), remotePort_(port), callback_(callback), socket_(socket)
    {
        assert (callback_);
    }

    void doWork() override;

protected:
    int remotePort_ = -1;
    std::string remoteHost_;
    IServerCallback *callback_ = nullptr;
    ConSocket *socket_ = nullptr;
};


#endif //LIBCONNECT_CONSERVER_H
