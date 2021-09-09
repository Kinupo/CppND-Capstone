#ifndef _CONNECTION_TESTER_CONNECTION_TESTER_H_
#define _CONNECTION_TESTER_CONNECTION_TESTER_H_

#include <memory>
#include <vector>
#include <string>
#include <map>

#include "connection_tester/connection_test_status.h"
#include "connection_tester/connection.h"
#include "connection_tester/protocols/not_found.h"

class ConnectionTester {
    private:
        std::vector<std::unique_ptr<Connection>> _connections;
        std::map<std::string, std::shared_ptr<Protocol>> _protocols;
    
    public:
        ConnectionTester();
        void RegisterProtocol(std::shared_ptr<Protocol> protocol);

        std::unique_ptr<Connection> MakeConnection(std::string name, std::string address, std::string protocol);

        void TestConnections(std::vector<std::unique_ptr<Connection>> connections);
        std::unique_ptr<std::vector<std::shared_ptr<ConnectionTestStatus>>> Status();
};

#endif