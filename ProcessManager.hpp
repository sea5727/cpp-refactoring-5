#ifndef __PROCESS_MANAGER_HPP__
#define __PROCESS_MANAGER_HPP__

#include "inc.hpp"

class ProcessManager
{
public:
    ProcessManager()
    {

    }
    ~ProcessManager()
    {

    }
    void add_routing(std::string key, std::shared_ptr<io_service_pool> routing)
    {
        routing_table.insert(make_pair(key, routing));
    }
    std::shared_ptr<io_service_pool> get_routings(std::string key)
    {
        if(routing_table.count(key) != 0)
        {
            return routing_table[key];
        }
        else
        {
            return std::shared_ptr<io_service_pool>(nullptr);
        }
    }
    boost::asio::io_service & get_routing_endpoint(std::string key)
    {
        return routing_table[key]->get_io_service();
    }
public:
     
    std::map<std::string, std::shared_ptr<io_service_pool>> routing_table;
};

#endif