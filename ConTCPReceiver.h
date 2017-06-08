//
// Created by pbeerken on 6/8/17.
//

#ifndef LIBCONNECT_CONTCPRECEIVER_H
#define LIBCONNECT_CONTCPRECEIVER_H

#include "ConThread.h"

class ConTCPReceiver : public ConRunnable
{
public:
    ConTCPReceiver(const std::string &host, int port)
            : remoteHost_(host), remotePort_(port)
    {
    }

    void doWork() override;

protected:
    bool connect();

    const std::string remoteHost_;
    int remotePort_;
    bool connected_ = false;
};


#endif //LIBCONNECT_CONTCPRECEIVER_H
