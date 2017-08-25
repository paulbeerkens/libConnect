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

class ConSocket
{
public:
    virtual bool connect(const struct sockaddr *address, socklen_t address_len) = 0;

    virtual ConSocket *accept(struct sockaddr *address, socklen_t *address_len) = 0;

    virtual bool isSocketSet() const =0;

    virtual bool createSocket()=0;

    virtual bool destroySocket()=0;

    virtual ssize_t read(void *buf, size_t count)=0;
    //virtual ssize_t test (int*)=0;
    /* more functions */
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

    bool connect(const struct sockaddr *address, socklen_t address_len) override
    {
        return ::connect(socket_, address, address_len) == 0;
    }

    ConSocketImpl *accept(struct sockaddr *address, socklen_t *address_len) override
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

    //virtual ssize_t test (int* t) {*t=1234; return 4;};
private:
    int socket_ = -1;
};

#endif //LIBCONNECT_CONSOCKET_H
