#ifndef __TCP_CONNECTOR_HPP__
#define __TCP_CONNECTOR_HPP__

#include "inc.hpp"

template <typename SessionHandler>
class TcpConnector
{
public:
    TcpConnector()
        : _connect_timeout_millisecond(10 * 1000)
        , _reconnect_interval_millisecond( 100 )
        , _deadline_timer_client_timeout(_io_service)
        , _resolver(_io_service)
        , _socket(_io_service)
    {
    } 
    ~TcpConnector()
    {
        std::cout << "Created TcpConnector" << std::endl;
    }
    
    void Connect()
    {
        std::cout << "Destroyed TcpConnector" << std::endl;
    }
    void start(std::string ip, std::string port)
    {
        std::cout << "TcpConnector start.." << std::endl;
        _ip = ip;
        _port = port;
        boost::asio::ip::tcp::resolver::iterator endpoint_iter = _resolver.resolve(boost::asio::ip::tcp::resolver::query(_ip, _port));
        start_connect(endpoint_iter);
        
        _connect_threads.emplace_back([&] {
            _io_service.run();
        });

        std::cout << "io_service end.. " << std::endl;
    }
    void start_connect(boost::asio::ip::tcp::resolver::iterator endpoint_iter)
    {
        std::cout << "TcpConnector start_connect.. start" << std::endl;
        if (endpoint_iter != boost::asio::ip::tcp::resolver::iterator())
        {
            std::cout << "[client:" << std::this_thread::get_id() << "] " ;
            std::cout << "Trying... to " << endpoint_iter->endpoint() << "... timeout : " << _connect_timeout_millisecond << std::endl;;

            
            auto handler = std::make_shared<SessionHandler> (_io_service);
            // handler->set_session_timeout(1000); //regist connect timeout
            
            //regist connect handler 
            boost::asio::async_connect(handler->socket(), endpoint_iter, 
                [=](const boost::system::error_code & error_code, boost::asio::ip::tcp::resolver::iterator endpoint_iter)
                {
                    handle_new_connection(handler, error_code, endpoint_iter);
                });
        }
        else 
        {
        }
        std::cout << "TcpConnector start_connect.. end" << std::endl;
    }

    void handle_new_connection( std::shared_ptr<SessionHandler> handler , const boost::system::error_code  & error_code, boost::asio::ip::tcp::resolver::iterator endpoint_iter)
    {
        handler->start(error_code);

       if(error_code) 
        {
            return; // 이부분 고려해보기
        }
        

        // std::cerr << "handler start " << std::endl;

        // auto new_handler = std::make_shared<SessionHandler> (_io_service);
        // boost::asio::async_connect(new_handler->socket(), endpoint_iter, 
        //     [=](const boost::system::error_code & error_code, boost::asio::ip::tcp::resolver::iterator endpoint_iter)
        //     {
        //         handle_new_connection(new_handler, error_code, endpoint_iter);
        //     });
    }


private:
    std::vector<std::thread> _connect_threads;
    bool stopped_;
    std::string _ip;
    std::string _port;
    int _connect_timeout_millisecond;
    int _reconnect_interval_millisecond;
    boost::asio::io_service _io_service;
    boost::asio::deadline_timer _deadline_timer_client_timeout;
    boost::asio::ip::tcp::resolver _resolver;
    // boost::asio::ip::tcp::resolver::iterator endpoint_iter;
    char buffer[8192];
protected:
    boost::asio::ip::tcp::socket _socket;
    
    
};

#endif