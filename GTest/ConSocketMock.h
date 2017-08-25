//
// Created by pbeerken on 8/24/17.
//

#ifndef LIBCONNECT_CONSOCKETMOCK_H
#define LIBCONNECT_CONSOCKETMOCK_H

#include "../ConSocket.h"
#include "gmock/gmock.h"


class ConSocketMock : public ConSocket
{
public:

    MOCK_METHOD2(connect, bool(
            const struct sockaddr*, socklen_t ));

    MOCK_METHOD2(accept, ConSocket*(
            struct sockaddr *, socklen_t *));

    MOCK_CONST_METHOD0(isSocketSet, bool());

    MOCK_METHOD0(createSocket, bool());

    MOCK_METHOD0(destroySocket, bool());

    MOCK_METHOD2(read, ssize_t(void * , size_t));

    bool socketSet_ = false;
};

#endif //LIBCONNECT_CONSOCKETMOCK_H
