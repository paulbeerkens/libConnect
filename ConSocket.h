//
// Created by pbeerken on 8/23/17.
//

#ifndef LIBCONNECT_CONSOCKET_H
#define LIBCONNECT_CONSOCKET_H

#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>

#include <iostream>

class ConSocket
{
public:
    virtual bool connect(const struct sockaddr *address, socklen_t address_len) = 0;

    virtual ConSocket *accept(struct sockaddr *address, socklen_t *address_len) = 0;

    virtual bool isSocketSet() const =0;

    virtual bool createSocket()=0;

    virtual bool destroySocket()=0;

    virtual ssize_t read(void *buf, size_t count)=0;

    virtual bool setsockopt(int level, int optname, const void *optval, socklen_t optlen)=0;

    virtual bool bind(const struct sockaddr *addr, socklen_t addrlen)=0;

    virtual bool listen(int backlog)=0;
};

class ConSocketImpl : public ConSocket
{
public:
    ConSocketImpl()
    {

    }

    ConSocketImpl(int sock) : socket_(sock)
    {
    }

    virtual ~ConSocketImpl()
    {
        std::cout << "ConSocketImpl::~ConSocketImpl" << std::endl;
    }

    bool connect(const struct sockaddr *address, socklen_t address_len) override
    {
        return ::connect(socket_, address, address_len) == 0;
    }

    ConSocket *accept(struct sockaddr *address, socklen_t *address_len) override
    {
        int s = ::accept(socket_, address, address_len);
        if (s == -1)
        {
            return nullptr;
        }
        return new ConSocketImpl(s);
    }

    bool isSocketSet() const override
    {
        return socket_ != -1;
    };

    bool createSocket() override
    {
        assert (socket_ == -1);
        socket_ = socket(PF_INET, SOCK_STREAM, 0);
        return socket_ == -1 ? false : true;
    }

    bool destroySocket() override
    {
        ::close(socket_);
        socket_ = -1;
    }

    ssize_t read(void *buf, size_t count) override
    {
        return ::read(socket_, (void *) buf, count);
    }

    bool setsockopt(int level, int optname, const void *optval, socklen_t optlen) override
    {
        return ::setsockopt(socket_, level, optname, optval, optlen) == 0;
    }

    virtual bool bind(const struct sockaddr *addr, socklen_t addrlen)
    {
        return ::bind(socket_, addr, addrlen) == 0;
    }

    virtual bool listen(int backlog)
    {
        return ::listen(socket_, backlog) == 0;
    }



private:
    int socket_ = -1;
};

#endif //LIBCONNECT_CONSOCKET_H
