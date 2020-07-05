#ifndef __INTERFACE_WORKER_HPP__
#define __INTERFACE_WORKER_HPP__

#include "inc.hpp"

class IWorker
{
public:
    virtual void start() = 0;
    virtual  boost::asio::io_service & get_io_service() = 0;
    virtual std::shared_ptr<io_service_pool> get_ptr_io_pool() = 0;
};

#endif