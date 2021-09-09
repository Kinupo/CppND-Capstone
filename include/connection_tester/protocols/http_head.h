#ifndef _CONNECTION_TESTER_PROTOCOLS_HTTP_HEAD_H_
#define _CONNECTION_TESTER_PROTOCOLS_HTTP_HEAD_H_

#include "connection_tester/protocol.h"

class HttpHead : public Protocol {
    public:
        HttpHead();
        std::string TestConnection(std::string address);
};

#endif