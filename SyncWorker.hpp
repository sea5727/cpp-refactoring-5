#ifndef __SYNC_WORKER_HPP__
#define __SYNC_WORKER_HPP__

#include "inc.hpp"

class SyncWorker : IWorker
{
using IntervalTaskType = std::function<void(const boost::system::error_code &, std::shared_ptr<boost::asio::deadline_timer>, int)>;
public:
    SyncWorker(std::size_t thread_count)
        : _worker_services(new io_service_pool(thread_count, thread_count))
    {
        boost::asio::io_service tio;
    }
    ~SyncWorker()
    {

    }
    void start()
    {
        _worker_services->run();
        // StartIntervalTask(&SyncWorker::PrintInterval, 1);
    }

    boost::asio::io_service & get_io_service()
    {
        return _worker_services->get_io_service();
    }

    std::shared_ptr<io_service_pool> get_ptr_io_pool()
    {
        return _worker_services;
    }
    void PrintInterval(const boost::system::error_code & error_code, int timer_id, int interval)
    {
        if(error_code)
        {
            std::cout << "[worker:" << std::this_thread::get_id() << "] ";
            std::cout << "this is interval task.. error_code : " << error_code.message() << std::endl;            
        }
        else
        {
            std::cout << "[worker:" << std::this_thread::get_id() << "] ";
            std::cout << "this is interval task.."<< std::endl;
            // RestartIntervalTask(ptr_dt, interval);
            RestartIntervalTask(&SyncWorker::PrintInterval, timer_id, interval);
        }


    }
    template<typename Object>
    void StartIntervalTask(void (Object::*fun)(const boost::system::error_code &, int, int), int interval)
    {
        std::vector<std::shared_ptr<boost::asio::io_service>> io_services = _worker_services->get_io_services();
                
        for(const auto & io : io_services)
        {
            int timer_id = deadline_timers.size();
            std::shared_ptr<boost::asio::deadline_timer> ptr_dt(new boost::asio::deadline_timer(*io, boost::posix_time::seconds(interval)));
            ptr_dt->async_wait(boost::bind(fun, this, boost::asio::placeholders::error, timer_id, interval));
            deadline_timers.push_back(ptr_dt);
        }
    }

    template<typename Object>
    void RestartIntervalTask(void (Object::*fun)(const boost::system::error_code &, int, int), int timer_id, int interval)
    {
        auto ptr_dt = deadline_timers[timer_id];
        ptr_dt->expires_from_now(boost::posix_time::seconds(interval));
        ptr_dt->async_wait(boost::bind(fun, this, boost::asio::placeholders::error, timer_id, interval));
    }
    void Task1(int a, int b)
    {
           
        std::cout << "[worker:" << std::this_thread::get_id() << "] " << "Task1.. interval : a : "  << a << " b : " << b << std::endl;
        
    }
    void Task2()
    {
        std::cout << "[worker:" << std::this_thread::get_id() << "] " << "Task2" << std::endl;
    }
    void Task3()
    {
        std::cout << "[worker:" << std::this_thread::get_id() << "] " << "Task3" << std::endl;
    }
    void Task4(const boost::system::error_code & error_code, std::shared_ptr<boost::asio::deadline_timer> ptr_dt, int interval)
    {
        std::cout << "[worker:" << std::this_thread::get_id() << "] " << "Task4" << std::endl;
    }

    void TestTask2(std::function<void()> f)
    {
        // std::function<void()> fun = boost::bind(f, this);
        // std::vector<std::function<void()>> funs;
        // funs.push_back(fun);
    }
    // template <typename member_function, typename... Args>
    // void add_work(int interval, member_function fun, Args... args)
    // {
    //     // boost::bind(fun, this, args...);
    //     // IntervalTaskType f = boost::bind(fun, this, args...);
    //     // _works.push_back(std::make_pair(f, interval));
    // }

    template <typename member_function, typename... Args>
    void add_work2(int interval, member_function fun, Args... args)
    {
        // IntervalTaskType f = boost::bind(fun, this, args...);
        // IntervalTaskType f = boost::bind(fun, this, args...);
        // _works.push_back(std::make_pair(f, interval));
    }


private:
    std::vector<std::pair<IntervalTaskType, int>> _works;
    std::shared_ptr<io_service_pool> _worker_services;
protected:
    std::vector<std::shared_ptr<boost::asio::deadline_timer>> deadline_timers;
};

#endif

