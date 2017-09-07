//
// Created by pbeerken on 9/7/17.
//

//
// Created by pbeerken on 5/20/17.
//

#include <iostream>

#include <gtest/gtest.h>
#include "../ConThread2.h"
#include <chrono>
#include <future>


class MyClassToBeRun2 : public ConThread2
{
public:
    MyClassToBeRun2(int loopSize)
            : loopSize_(loopSize)
    {
        std::cout << "MyClassToBeRun2 called with " << loopSize << " i_=" << i_ << std::endl;
    }

    void doWork() override
    {
        startPromise_.get_future().wait();
        for (long j = 0; j < loopSize_ && requestedToTerminate_ == false; j++)
        {
            ++i_;
        }

        endPromise_.set_value();
    }

    long i_ = 0;
    long loopSize_ = 0;

    std::promise<void> startPromise_;
    std::promise<void> endPromise_;
};


TEST(MyConThread2Test, TestThatItRunsInASeparateThread)
{
    MyClassToBeRun2 ct(10'000);
    EXPECT_EQ (0, ct.i_);
    ct.startPromise_.set_value();
    ct.endPromise_.get_future().wait();
    EXPECT_EQ (10000, ct.i_);
}

TEST(MyConThread2Test, TestThatCanBeDestroyed)
{
    MyClassToBeRun2 ct(1'000'000'000);
    ct.startPromise_.set_value();
}