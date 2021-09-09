#ifndef _CONNECTION_TESTER_PROTOCOLS_NOT_FOUND_H_
#define _CONNECTION_TESTER_PROTOCOLS_NOT_FOUND_H_

#include "connection_tester/protocol.h"

class ProtocolNotFound : public Protocol {
    public:
        std::string TestConnection(std::string address);
};


#endif