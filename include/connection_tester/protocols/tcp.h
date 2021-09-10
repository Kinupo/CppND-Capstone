#ifndef _CONNECTION_TESTER_PROTOCOLS_HTTP_HEAD_H_
#define _CONNECTION_TESTER_PROTOCOLS_HTTP_HEAD_H_

#include <iostream>
#include <thread>
#include <future>

#include <boost/beast.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>

#include "connection_tester/protocol.h"

class Tcp : public Protocol {
    public:
        Tcp();
        std::string TestConnection(std::string address);
};

#endif