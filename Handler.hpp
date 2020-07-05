#ifndef __HANDLER_HPP__
#define __HANDLER_HPP__

#include "inc.hpp"

class ActualMessage1;
class ActualMessage2;
class Message;

class Handler
{
public:
    virtual void handle(ActualMessage1& msg) = 0;
    virtual void handle(ActualMessage2& msg) = 0;

    virtual void handle(Message& msg) {}
};


class ActualHandler1 : public Handler
{
public:
    virtual void handle(ActualMessage1 & msg) override;
        // std::cout << "this is ActualMessage1 msg handle of ActualHandler1" << std::endl;
    virtual void handle(ActualMessage2 & msg) override
    {
        std::cout << "this is ActualMessage2 msg handle of ActualHandler1" << std::endl;
    }
};

class ActualHandler2 : public Handler
{
public:
    virtual void handle(ActualMessage1 & msg) override
    {
        std::cout << "this is ActualMessage1 msg handle of ActualHandler2" << std::endl;
    }
    virtual void handle(ActualMessage2 & msg) override
    {
        std::cout << "this is ActualMessage2 msg handle of ActualHandler2" << std::endl;
    }
};



#endif