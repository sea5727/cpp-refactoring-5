#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include "inc.hpp"


#include <arpa/inet.h>
// uint32_t htonl(uint32_t hostlong);
// uint16_t htons(uint16_t hostshort);
// uint32_t ntohl(uint32_t netlong);
// uint16_t ntohs(uint16_t netshort);


class ActualHandler1;
class Handler;

class Message
{
public:

public:
    virtual void print() { std::cout << "this is message" << std::endl; }
    void dispatch(ActualHandler1 & handler)
    {
        std::cout << "this is dispatch of Message" << std::endl;

        dispatchImpl(handler);
    }
protected:
    virtual void virtualTest()
    {
        std::cout << "this is virtualTest of Message" << std::endl;
    }
    virtual void dispatchImpl(Handler & handler) = 0;
    
};


template <typename TDerived>
class MessageBase : public Message
{
protected:
    virtual void dispatchImpl(Handler& handler) override
    {
        std::cout << "this is dispatchImpl of MessageBase" << std::endl;
        handler.handle(static_cast<TDerived&>(*this)); // 자식 class로 변경
    }
};

class ActualMessage1 : public MessageBase<ActualMessage1>
{
public:
    int a;
    int b;
    int c;
    short d;
    char e;
    char f[3];
};


class ActualMessage2 : public MessageBase<ActualMessage2>
{
protected:
    // virtual void dispatchImpl(Handler & handler) override
    // {
    //     std::cout << "this is dispatchImpl of ActualMessage1" << std::endl;
    //     // handler.handle(*this);
    // }
};




#endif