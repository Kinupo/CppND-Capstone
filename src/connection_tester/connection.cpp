#include "connection_tester/connection.h"

#include <thread>

Connection::Connection(std::string name, std::string address, std::shared_ptr<Protocol> _protocol)
 : _name(name), _address(address), _protocol(_protocol){}

long ComputeDuration(std::chrono::_V2::system_clock::time_point& test_start){
    auto test_end = std::chrono::system_clock::now();
    auto duration_ns = test_end - test_start;
    return duration_ns.count()/Connection::kNanoSecondsToMilliseconds;
}

void ConnectionTest(
    std::string address, 
    std::shared_ptr<Protocol>& protocol,
    std::string& status,
    std::chrono::_V2::system_clock::time_point test_start,
    long& duration_ms,
    bool& test_is_running){
    
    status = protocol->TestConnection(address);
    duration_ms = ComputeDuration(test_start);
    test_is_running = false;
}

void Connection::TestConnection() {

    if(_test_is_running)
        return;
    
    _status = "Connecting";
    _test_is_running = true;
    _test_start = std::chrono::system_clock::now();
    std::thread connection_test_thread(
        ConnectionTest,
            _address, 
            std::ref(_protocol),
            std::ref(_status), 
            _test_start, 
            std::ref(_duration_ms), 
            std::ref(_test_is_running));
    connection_test_thread.detach();
}

std::unique_ptr<ConnectionTestStatus> Connection::Status(){
    auto status = std::make_unique<ConnectionTestStatus>();
    status->protocol_name = _protocol->Name();
    status->name = _name;
    status->status = _status;
    if(_test_is_running)
        _duration_ms = ComputeDuration(_test_start);
    status->duration_ms = _duration_ms;
    return status;
}