//
// Created by pbeerken on 5/18/17.
//

#ifndef LIBCONNECT_CONSTANDALONECONNECTION_H
#define LIBCONNECT_CONSTANDALONECONNECTION_H


#include <string>


struct IConnectionCallback
{
    virtual void onConnected ()=0;
    virtual void onDisconnected ()=0;
    virtual void onMsg ()=0;
};

class StandAloneConnection
{
public:
    StandAloneConnection (const std::string& host, long port)
    :host_ (host), port_(port)
    {};

    //IConnection


protected:
    std::string host_;

protected:
    long port_;
};


#endif //LIBCONNECT_CONSTANDALONECONNECTION_H
