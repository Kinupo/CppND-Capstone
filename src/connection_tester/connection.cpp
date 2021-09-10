#include "connection_tester/connection.h"

Connection::Connection(std::string name, std::string address, std::shared_ptr<Protocol> _protocol)
 : _name(name), _address(address), _protocol(_protocol){}

long Connection::ComputeDuration(){
    auto test_end = std::chrono::system_clock::now();
    auto duration_ns = test_end - _test_start;
    return duration_ns.count()/kNanoSecondsToMilliseconds;
}

void Connection::ConnectionTest(){
//     std::string& address, 
//     std::shared_ptr<Protocol> protocol,
//     std::string& status,
//     std::chrono::_V2::system_clock::time_point& test_start){
    
    _status = _protocol->TestConnection(_address);
    _duration_ms = ComputeDuration();
    _test_is_running = false;
}

void Connection::TestConnection() {

    if(_test_is_running)
        return;
    
    _status = "Connecting";
    _test_is_running = true;
    _test_start = std::chrono::system_clock::now();
    ConnectionTest();
}

std::unique_ptr<ConnectionTestStatus> Connection::Status(){
    auto status = std::make_unique<ConnectionTestStatus>();
    status->protocol_name = _protocol->Name();
    status->name = _name;
    status->status = _status;
    if(_test_is_running)
        _duration_ms = ComputeDuration();
    status->duration_ms = _duration_ms;
    return status;
}