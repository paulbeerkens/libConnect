//
// Created by pbeerken on 5/18/17.
//

#ifndef LIBCONNECT_CONTHREAD_H
#define LIBCONNECT_CONTHREAD_H

#include <thread>
#include <future>

class ConRunnable
{
public:
    virtual void doWork ()=0;
    void requestToTerminate () {requestedToTerminate_=true;};
protected:
   bool requestedToTerminate_=false;
};

template <class ClassToRun>
class ConThread
{
public:
    //constructor forwards arguments to the ClassToRun constructor
    template <typename ... Arguments > ConThread (Arguments ... args)
            :toRun_ (args ...)
             , t_ ([this] {
                started_.set_value();
                toRun_.doWork();
            })
    {
        started_.get_future().wait(); //wait till the thread is really started
    }

    ~ConThread()
    {
        toRun_.requestToTerminate ();
        if (t_.joinable ()){
            t_.join ();
        }
    }
    void requestToTerminate () {toRun_.requestToTerminate ();};

    std::thread& getThread () {return t_;};

    ClassToRun& get () {return toRun_;};
private:
    std::promise <void> started_;
    ClassToRun toRun_;
    std::thread t_;
};

#endif //LIBCONNECT_CONTHREAD_H
