#include "inc.hpp"

void ActualHandler1::handle(ActualMessage1 & msg)
{
    std::cout << "this is ActualMessage1 msg handle of ActualHandler1" << std::endl;
    msg.print();
}