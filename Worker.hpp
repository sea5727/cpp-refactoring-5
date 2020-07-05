#ifndef __WORKER_HPP__
#define __WORKER_HPP__

#include "inc.hpp"

class Worker : IWorker
{
public:
    Worker(size_t io_count, size_t thread_count)
        : _worker_services(new io_service_pool(io_count, thread_count))
    {

    }
    ~Worker()
    {

    }
    void start()
    {
        _worker_services->run();
        
    }

    boost::asio::io_service & get_io_service()
    {
        return _worker_services->get_io_service();
    }

    std::shared_ptr<io_service_pool> get_ptr_io_pool()
    {
        return _worker_services;
    }

private:
    std::shared_ptr<io_service_pool> _worker_services;
};

#endif