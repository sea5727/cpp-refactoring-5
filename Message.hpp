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
    // int a;
    // int b;
    // int c;
    // short d;
    // char e;
    // char f[3];
public:
    virtual void print();
    void dispatch(ActualHandler1 & handler)
    {
        std::cout << "this is dispatch of Message" << std::endl;
        // virtualTest();

        // dispatchImpl(handler);
    }
protected:
    void virtualTest()
    {
        std::cout << "this is virtualTest of Message" << std::endl;
    }
    // virtual void dispatchImpl(Handler & handler);
// public:
//     void ntoh()
//     {
//         a = ntohl(a);
//         b = ntohl(b);
//         c = ntohl(c);
//         d = ntohs(d);
//     }
//     void hton()
//     {
//         a = htonl(a);
//         b = htonl(b);
//         c = htonl(c);
//         d = htons(d);
//     }
//     void get_to_buffer(char *buffer , size_t size)
//     {
//         memcpy(buffer, this, size);
//     }
//     void set_from_buffer(char * buffer, size_t size)
//     {
//         memcpy(this, buffer, size);
//     }
    
};
class TestMessage : public Message
{
public:
    void print() override;
    
    void virtualTest()
    {
        std::cout << "this is virtualTest of TestMessage" << std::endl;
    }
    void dispatchImpl(Handler & handler)
    {
        std::cout << "this is dispatchImpl.. of TestMessage" << std::endl;
    }
};


// template <typename TDerived>
// class MessageBase : public Message
// {
// protected:
//     virtual void dispatchImpl(Handler& handler) override
//     {
//         std::cout << "this is dispatchImpl of MessageBase" << std::endl;
//         handler.handle(static_cast<TDerived&>(*this)); 
//     }
// };

// class ActualMessage1 : public Message //: public MessageBase<ActualMessage1>
// {
// protected:
//     virtual void dispatchImpl(Handler & handler) override
//     {
//         std::cout << "this is dispatchImpl of ActualMessage1" << std::endl;
//         handler.handle(*this);
//     }
// };


// class ActualMessage2 : public Message// : public MessageBase<ActualMessage2>
// {
// protected:
//     virtual void dispatchImpl(Handler & handler) override
//     {
//         std::cout << "this is dispatchImpl of ActualMessage1" << std::endl;
//         // handler.handle(*this);
//     }
// };




#endif