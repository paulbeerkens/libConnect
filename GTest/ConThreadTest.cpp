//
// Created by pbeerken on 5/20/17.
//

#include <iostream>

#include <gtest/gtest.h>
#include "../ConThread.h"
#include <chrono>
#include <future>


class MyClassToBeRun: public ConRunnable
{
public:
    MyClassToBeRun (int loopSize)
            :loopSize_ (loopSize)
    {};

    void doWork () override
    {
        startPromise_.get_future ().wait ();
        for (long j=0; j<loopSize_ && requestedToTerminate_==false; j++)
        {
            ++i_;
        }

        endPromise_.set_value();
    }
    long i_=0;
    long loopSize_=0;

    std::promise <void> startPromise_;
    std::promise <void> endPromise_;
};


TEST(MyConThread2Test, TestThatItRunsInASeparateThread)
{
    ConThread<MyClassToBeRun> ct (10'000);
    EXPECT_EQ (0,ct.get ().i_);
    ct.get ().startPromise_.set_value ();
    ct.get ().endPromise_.get_future ().wait ();
    EXPECT_EQ (10000,ct.get ().i_);
}

TEST(MyConThread2Test, TestThatCanBeDestroyed)
{
    ConThread<MyClassToBeRun> ct (1'000'000'000);
    ct.get ().startPromise_.set_value ();
}