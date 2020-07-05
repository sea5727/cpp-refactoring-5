#ifndef __INC_HPP__
#define __INC_HPP__

#include <stdio.h>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/chrono.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/noncopyable.hpp>
#include <boost/bind/bind.hpp>
#include <boost/signals2.hpp>
#include <boost/any.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <memory>
#include <map>

#include "lib/io_service_pool.hpp"

#include "TcpSession.hpp"

#include "TcpAcceptor.hpp"
// #include "TcpServerSession.hpp"

// #include "ClientSession.hpp"
#include "IWorker.hpp"
#include "Worker.hpp"
#include "SyncWorker.hpp"
#include "ProcessManager.hpp"

// #include "TcpClientSession.hpp"
// #include "TcpClientChat.hpp"

#include "TcpConnector.hpp"
#include "ApplicationTcpSession.hpp"

#include "Handler.hpp"
#include "Message.hpp"
// #include "TcpConnectorSession.hpp"
// #include "TcpConnectorSessionChild.hpp"

// extern ProcessManager pm;



#endif
