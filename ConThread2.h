//
// Created by pbeerken on 9/7/17.
//

#ifndef LIBCONNECT_CONTHREAD2_H
#define LIBCONNECT_CONTHREAD2_H

#include <pthread.h>
#include <assert.h>
#include <future>
#include <libLog/Logger.h>

class ConThread2
{

public:
    ConThread2()
    {
        if (pthread_create(&pthreadt_, nullptr, &ConThread2::run, this))
        {

        }

        //wait till the thread is started to avoid shutdown issues
        started_.get_future().wait();
    };

    virtual ~ConThread2()
    {
        waitToTerminate(5);
        assert (running_ == false);
    }

    virtual void doWork()=0;

    void requestToTerminate()
    {
        requestedToTerminate_ = true;
    };

    void waitToTerminate(int seconds = 60)
    {
        requestToTerminate();
        if (seconds > 0)
        {
            std::future_status status = finished_.get_future().wait_for(std::chrono::seconds(seconds));
            if (status == std::future_status::timeout)
            {
                Logger::Instance().logError() << "Failed to terminate thread in time (" << seconds
                                              << " seconds). Going to try pthread_cancel" << LogStream::endl;
                pthread_cancel(pthreadt_);
            }

        } else
        {
            //wait indefinitely
            finished_.get_future().wait();
        }
    }

protected:
    static void *run(void *conthread)
    {
        ConThread2 *t = static_cast <ConThread2 *> (conthread);
        t->running_ = true;
        t->started_.set_value();

        if (!t->requestedToTerminate_)
        {
            t->doWork();
        }
        t->running_ = false;
        t->finished_.set_value();
    }

    bool requestedToTerminate_ = false;
    bool running_ = false;
    pthread_t pthreadt_;
    std::promise<void> started_;
    std::promise<void> finished_;
};


#endif //LIBCONNECT_CONTHREAD2_H
