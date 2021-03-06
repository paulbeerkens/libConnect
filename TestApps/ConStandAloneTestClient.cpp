//
// Created by pbeerken on 7/24/17.
//

#include "../ConStandAloneConnection.h"
#include "../ConTCPReceiver.h"
#include <iostream>

struct MyCallBack : public IConnectionCallback
{
    void onConnected() override
    {
        std::cout << "MyCallBack::onConnected ()" << std::endl;
    };

    void onDisconnected() override
    {
        std::cout << "MyCallBack::onDisconnected ()" << std::endl;
    };

    void onMsg() override
    {
        std::cout << "MyCallbBack::onMsg ()" << std::endl;
    };
};

int main()
{
    MyCallBack cb;
    ConThread<ConTCPReceiver> connection("127.0.0.1", 9877, &cb);
    std::this_thread::sleep_for(std::chrono::milliseconds(500000));
    return 0;
}