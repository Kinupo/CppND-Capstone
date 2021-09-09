#ifndef _CONNECTION_TESTER_CONNECTION_TESTER_H_
#define _CONNECTION_TESTER_CONNECTION_TESTER_H_

#include <memory>
#include <vector>
#include <string>

#include "connection_tester/connection_test_status.h"
#include "connection_tester/connection.h"

class ConnectionTester {
    private:
        std::vector<std::unique_ptr<Connection>> _connections;
    public:
        void TestConnections(std::vector<std::unique_ptr<Connection>> connections);

        std::unique_ptr<Connection> MakeConnection(std::string name, std::string address, std::string protocol);

        std::unique_ptr<std::vector<std::shared_ptr<ConnectionTestStatus>>> Status();
};

#endif