#include "inc.hpp"

// ProcessManager pm;

int main(int, char**) {

    // auto msg = std::shared_ptr<ActualMessage1>();
    // ActualHandler1 handler1;
    // std::cout << "sizeof. " <<sizeof(ActualHandler1) << std::endl;
    // handler1.handle(*(msg.get()));
    // std::cout << "msg->dispatch start " << std::endl;
    // msg->dispatch(handler1);

    // auto msg = std::make_shared<ActualMessage1>();
    // msg->print();
    ActualMessage1 msg; // buffer에서 파서가 해당 message를 리턴해줘야한다.?
    ActualHandler1 handler1; // Handler는 그때그때 ? 
    std::cout << "msg->dispatch start " << std::endl;
    // msg->dispatch(handler1);
    msg.dispatch(handler1);



    return 0;


    TcpAcceptor<ApplicationTcpSession> tmf;
    SyncWorker worker(2);

    // pm.add_routing("tmf", tmf.get_ptr_io_pool());
    // pm.add_routing("worker", worker.get_ptr_io_pool());

    
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
