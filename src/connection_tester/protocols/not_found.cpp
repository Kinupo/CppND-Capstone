#include "connection_tester/protocols/not_found.h"

ProtocolNotFound::ProtocolNotFound(std::string name) : Protocol(name){};

std::string ProtocolNotFound::TestConnection(std::string address){
    return "Unsupported protocol";
}