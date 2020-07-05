#ifndef __TCP_SESSION_HPP__
#define __TCP_SESSION_HPP__

#include "inc.hpp"

class TcpSession : public std::enable_shared_from_this<TcpSession> 
{
public :
    TcpSession(boost::asio::io_service & io_service)
        : _io_service(io_service)
        , _socket(io_service)
        , _strand(io_service)
        , _session_timeout_timer(io_service)
    {
        std::cout << "[client:" << std::this_thread::get_id() << "]" << "Created TcpSession" << std::endl;
        memset(buffer, 0x00, sizeof(buffer));
    }
    ~TcpSession()
    {
        std::cout << "[client:" << std::this_thread::get_id() << "]" << "Destroyed TcpSession" << std::endl;
    }
public :
    void start(const boost::system::error_code & error_code)
    {
        _session_timeout_timer.cancel();
        OnConnected(error_code);
        if(!error_code)
        {
            read_packet();
        }
    }
    boost::asio::ip::tcp::socket & socket()
    {
        return _socket;
    }
    void read_packet()
    {
        boost::asio::async_read( _socket, 
                                boost::asio::buffer(buffer),
                                boost::asio::transfer_at_least(1),
                                [me=shared_from_this()](const boost::system::error_code & error_code, std::size_t read_size){
                                    me->read_packet_done(error_code, read_size);
                                });
    }
    void read_packet_done(const boost::system::error_code & error_code, std::size_t read_size)
    {
        if(error_code) 
        {
            std::cout << "read_packet_done error : " << error_code.message() << std::endl;
            try 
            { 
                _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                _socket.close();
            }
            catch(std::exception const& e) 
            {
                std::cerr << "catch!! e.what : " << e.what() << std::endl; 
            }
            catch(...) 
            { 
                std::cerr << "whoops!" << std::endl; 
            }
            OnClosed();
            return;
        }
        OnReaded(buffer, read_size);
        read_packet();
    }
    void send_packet(char* send_buffer, std::size_t size)
    {
        boost::asio::async_write(_socket, 
                                  boost::asio::buffer(send_buffer, size), 
                                [me=shared_from_this()](boost::system::error_code error_code, std::size_t write_size){
                                    me->write_packet_done(error_code, write_size);

        });
    }
    void write_packet_done(boost::system::error_code error_code, std::size_t write_size)
    {
        if(error_code)
        {
            std::cerr << "write_packet_done.. error: " << error_code.message() << std::endl;
            return;
        }
        OnWrited();
    }
    

    void start_callback_with_interval(
        std::function<void(const boost::system::error_code &, std::weak_ptr<boost::asio::deadline_timer>, int)> callback, 
                                                                                                            int interval) 
    {
        std::shared_ptr<boost::asio::deadline_timer> ptr_dt(new boost::asio::deadline_timer(_io_service));
        std::weak_ptr<boost::asio::deadline_timer> w_ptr_dt(ptr_dt);
        ptr_dt->expires_from_now(boost::posix_time::seconds(interval));
        ptr_dt->async_wait([=](const boost::system::error_code & error_code){
            callback(error_code, w_ptr_dt, interval);
        });
        deadline_timers.push_back(ptr_dt); // pool에 timer를 가지고 있어야, Session이 종료되어 destructor 가 수행될때 타이머도 같이 해제된다. 나머지는 weak로 전달해준다.
    }
    void restart_callback_with_interval(
        std::function<void(const boost::system::error_code &, std::weak_ptr<boost::asio::deadline_timer>, int)> callback, 
                                                                     std::weak_ptr<boost::asio::deadline_timer> w_ptr_dt, 
                                                                                                            int interval) 
    {
        auto ptr_dt = w_ptr_dt.lock();
        if(ptr_dt)
        {
            ptr_dt->expires_at(ptr_dt->expires_at() + boost::posix_time::seconds(interval));
            // ptr_dt->expires_from_now(boost::posix_time::seconds(interval));
            ptr_dt->async_wait([=](const boost::system::error_code & error_code) {
                callback(error_code, w_ptr_dt, interval);
            });
        }
    }



    virtual void OnClosed() = 0;
    virtual void OnConnected(const boost::system::error_code & error_code) = 0;
    virtual void OnReaded(char read_data[], std::size_t size) = 0;
    virtual void OnWrited() = 0;

public:
    char buffer[8192];
    boost::asio::io_service & _io_service;
    boost::asio::ip::tcp::socket _socket;
    boost::asio::io_service::strand _strand;
    boost::asio::deadline_timer _session_timeout_timer;
protected:
    std::vector<std::shared_ptr<boost::asio::deadline_timer>> deadline_timers;
    std::function<void()>  mOnCall;
};
#endif