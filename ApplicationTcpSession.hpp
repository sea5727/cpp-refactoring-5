#ifndef __APPLICATION_TCP_SESSION_HPP__
#define __APPLICATION_TCP_SESSION_HPP__

#include "inc.hpp"

class ApplicationTcpSession : public TcpSession {

public :
    ApplicationTcpSession(boost::asio::io_service & io_service) : TcpSession(io_service)
    {
        std::cout << "[ApplicationTcpSession:" << std::this_thread::get_id() << "]" << "Created ApplicationTcpSession" << std::endl;
    }
    
    ~ApplicationTcpSession()
    {
        std::cout << "[ApplicationTcpSession:" << std::this_thread::get_id() << "]" << "Destroyed ApplicationTcpSession" << std::endl;
    }
  
    
    void PrintInterval(const boost::system::error_code & error_code, std::weak_ptr<boost::asio::deadline_timer> ptr_dt, int interval)
    {
        if(error_code)
        {
            std::cout << "[ApplicationTcpSession:" << std::this_thread::get_id() << "] ";
            std::cout << "this is interval task.. error_code : " << error_code.message() << std::endl;            
        }
        else
        {
            std::cout << "[ApplicationTcpSession:" << std::this_thread::get_id() << "] ";
            std::cout << "this is interval task.."<< std::endl;
            
            restart_callback_with_interval(boost::bind(&ApplicationTcpSession::PrintInterval, this, boost::asio::placeholders::error, boost::placeholders::_2, boost::placeholders::_3), ptr_dt, interval);
        }
    }
    
    void OnConnected(const boost::system::error_code & error_code);
    void OnClosed();
    void OnReaded(char read_buffer[], std::size_t size);
    void OnWrited();

public :


};

#endif