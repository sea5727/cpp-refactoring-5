#ifndef __TCP_ACCEPTOR_HPP__
#define __TCP_ACCEPTOR_HPP__

#include "inc.hpp"


template <typename SessionHandler>
class TcpAcceptor
{
    using shared_hantler_t = std::shared_ptr<SessionHandler>;
public : 
    TcpAcceptor()
         : _io_service(1)
         , _acceptor(_io_service)
         , _if_services(new io_service_pool(8))
    {
    }
    void start(uint16_t port)
    {
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
        _acceptor.open(endpoint.protocol());
        _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        _acceptor.bind(endpoint);
        _acceptor.listen();

        auto handler = std::make_shared<SessionHandler> (_if_services->get_io_service());
        
        _acceptor.async_accept( handler->socket(),
                                [=](boost::system::error_code error_code){
                                    handle_new_connection(handler, error_code);
                                });
        
        _if_services->run();
        _accept_threads.emplace_back([&] {
            _io_service.run();
        });

    }
    boost::asio::io_service & get_if_service()
    {
        return _if_services->get_io_service();
    }
    std::shared_ptr<io_service_pool> get_ptr_io_pool()
    {
        return _if_services;
    }
private:
    void handle_new_connection( shared_hantler_t handler , const boost::system::error_code & error_code)
    {
        handler->start(error_code);
        if(error_code) 
        {
            std::cerr << "handle_new_connection.. error : " << error_code.message() << std::endl;
            return; // 이부분 고려해봐야할듯?
        }
        

        auto new_handler = std::make_shared<SessionHandler> (_if_services->get_io_service());
        
        _acceptor.async_accept( new_handler->socket(), 
                                [=](boost::system::error_code error_code) {
                                    handle_new_connection(new_handler, error_code );
                                });
    }


private:
    std::vector<std::thread> _accept_threads;
    boost::asio::io_service _io_service;
    boost::asio::ip::tcp::acceptor _acceptor;
    std::shared_ptr<io_service_pool> _if_services;
};

#endif