//
// Created by pbeerken on 6/8/17.
//

#include "ConTCPReceiver.h"
//#include <thread>
//#include <chrono>

void ConTCPReceiver::doWork()
{
    while (!requestedToTerminate_)
    {
        while (!requestedToTerminate_ && !connected_)
        {
            if (!connect())
            {//if not sucesfully connected wait and try again
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        while (connected_)
        {
            //read message
        }
    }

}

bool ConTCPReceiver::connect()
{
    return false;
}