//
// Created by pbeerken on 5/18/17.
//

#ifndef LIBCONNECT_CONSTANDALONECONNECTION_H
#define LIBCONNECT_CONSTANDALONECONNECTION_H


#include <string>



class StandAloneConnection
{
public:
    StandAloneConnection (const std::string& host, long port)
    :host_ (host), port_(port)
    {};

    //IConnection


protected:
    std::string host_;
    long port_;
};


#endif //LIBCONNECT_CONSTANDALONECONNECTION_H
