//
// Created by pbeerken on 7/24/17.
//

#ifndef LIBCONNECT_CONCONNECTIONCALLBACK_H
#define LIBCONNECT_CONCONNECTIONCALLBACK_H


struct IConnectionCallback
{
    virtual void onConnected()=0;

    virtual void onDisconnected()=0;

    virtual void onMsg()=0;
};


#endif //LIBCONNECT_CONCONNECTIONCALLBACK_H
