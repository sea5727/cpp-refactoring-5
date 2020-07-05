#include "inc.hpp"

ProcessManager pm;

int main(int, char**) {
    TcpAcceptor<ApplicationTcpSession> tmf;
    SyncWorker worker(2);

    pm.add_routing("tmf", tmf.get_ptr_io_pool());
    pm.add_routing("worker", worker.get_ptr_io_pool());

    
    std::cout << "[main:" << std::this_thread::get_id() << "]" << "thread start" << std::endl;
    worker.start();
    tmf.start(5103);

    TcpConnector<ApplicationTcpSession> client;
    std::cout << "start?" << std::endl;
    client
        .start("192.168.0.34", "5103");



    std::cout << "[main:" << std::this_thread::get_id() << "]" << "while start" << std::endl;
    while(1)
    {   
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

}
