#include "connection_tester/connection_tester.h"

ConnectionTester::ConnectionTester(){}

void ConnectionTester::TestConnections(std::vector<std::unique_ptr<Connection>> connections){
    _connections.clear();
    for(auto& connection:connections){
        connection->TestConnection();
        _connections.emplace_back(std::move(connection));
    }
}

void ConnectionTester::RegisterProtocol(std::shared_ptr<Protocol> protocol){
    _protocols[protocol->Name()] = protocol;
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
        
    std::shared_ptr<Protocol> protocol_instance;
    if(_protocols.find(protocol) == _protocols.end())
        protocol_instance = std::make_shared<ProtocolNotFound>(protocol);
    else
        protocol_instance = _protocols[protocol];

    return std::make_unique<Connection>(name, address, protocol_instance);
}
