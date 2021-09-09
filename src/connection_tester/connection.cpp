#include "connection_tester/connection.h"

Connection::Connection(std::string name, std::string address, std::shared_ptr<Protocol> _protocol)
 : _name(name), _address(address), _protocol(_protocol){}

void Connection::TestConnection() {

    if(_test_is_running)
        return;
    
    _status = "Connecting";
    _test_is_running = true;
    _test_start = std::chrono::system_clock::now();
    _status = _protocol->TestConnection(_address);
    auto test_end = std::chrono::system_clock::now();
    auto duration_ns = test_end - _test_start;
    _duration_ms = duration_ns.count()/kNanoSecondsToMilliseconds;
    _test_is_running = false;
}

std::unique_ptr<ConnectionTestStatus> Connection::Status(){
    auto status = std::make_unique<ConnectionTestStatus>();
    status->protocol_name = _protocol->Name();
    status->name = _name;
    status->status = _status;
    status->duration_ms = _duration_ms;
    return status;
}