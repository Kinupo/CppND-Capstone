#ifndef _CONFIGURATION_CONNECTION_TESTER_CONFIGURATION_H_
#define _CONFIGURATION_CONNECTION_TESTER_CONFIGURATION_H_

#include "connection_tester/connection_tester.h"
#include "connection_tester/protocols/tcp.h"

namespace ConnectionTesterConfiguration {

    std::unique_ptr<ConnectionTester> GenerateConnectionTester(){
        auto connection_tester = std::make_unique<ConnectionTester>();
        connection_tester->RegisterProtocol(std::make_shared<Tcp>());
        return connection_tester;
    }
      

};

#endif