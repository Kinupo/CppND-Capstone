#include "connection_tester/connection_tester.h"
#include "connection_tester/protocols/http_head.h"

void ConnectionTester::TestConnections(std::vector<std::unique_ptr<Connection>> connections){
    _connections.clear();
    for(auto& connection:connections){
        connection->TestConnection();
        _connections.emplace_back(std::move(connection));
    }
}

std::unique_ptr<std::vector<std::shared_ptr<ConnectionTestStatus>>> ConnectionTester::Status(){
    auto results = std::make_unique<std::vector<std::shared_ptr<ConnectionTestStatus>>>();
    for(auto& connection:_connections)
        results->emplace_back(connection->Status());
    return results;
}

std::unique_ptr<Connection> ConnectionTester::MakeConnection(
    std::string name, 
    std::string address, 
    std::string protocol){
        auto protocol_instance = std::make_shared<HttpHead>();
        return std::make_unique<Connection>(name, address, protocol_instance);
    }
