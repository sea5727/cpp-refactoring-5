#include "inc.hpp"


void ApplicationTcpSession::OnConnected(const boost::system::error_code & error_code)
{
    if(error_code)
    {
        std::cout << "ApplicationTcpSession::OnConnected .. error_code : " << error_code.message() << std::endl;
    }
    else 
    {
        std::cout << "ApplicationTcpSession::OnConnected .. " << std::endl;
        start_callback_with_interval(boost::bind(&ApplicationTcpSession::PrintInterval, this, boost::asio::placeholders::error, boost::placeholders::_2, boost::placeholders::_3), 1);
    }
    
}
void ApplicationTcpSession::OnReaded(char read_data[], std::size_t size) 
{ 
    std::cout << "ApplicationTcpSession::OnReaded" << std::endl;
    // std::shared_ptr<char> p_buffer(new char[size], std::default_delete<char[]>());
    // std::copy(read_data, read_data + size, p_buffer.get());


    // auto &io = pm.get_routing_endpoint("worker");
    // io.post([p_buffer, size]{
    //     std::cout << "[worker:" << std::this_thread::get_id() << "]" << "(" << size << ")" << p_buffer  << std::endl;
    // });
}


void ApplicationTcpSession::OnWrited()
{
    std::cout << "ApplicationTcpSession::OnWrited" << std::endl;
    // std::cout << "[worker:" << std::this_thread::get_id() << "]" << "OnWrited!!!" << std::endl;
}

void ApplicationTcpSession::OnClosed()
{
    std::cout << "ApplicationTcpSession::OnClosed" << std::endl;
}

