#ifndef _CONNECTION_TESTER_PROTOCOLS_HTTP_HEAD_H_
#define _CONNECTION_TESTER_PROTOCOLS_HTTP_HEAD_H_

#include <iostream>

#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>

#include "connection_tester/protocol.h"

class HttpHead : public Protocol {
    public:
        HttpHead();
        std::string TestConnection(std::string address);
};

#endif