#include "connection_tester/protocol.h"

Protocol::Protocol(std::string name) 
    : _name(name){}

std::string Protocol::Name(){return _name;}