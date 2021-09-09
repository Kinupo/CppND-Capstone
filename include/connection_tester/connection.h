#ifndef _CONNECTION_TESTER_CONNECTION_H_
#define _CONNECTION_TESTER_CONNECTION_H_

#include <string>
#include <memory>
#include <vector>
#include <chrono>

#include "connection_tester/connection_test_status.h"
#include "connection_tester/protocol.h"

class Connection{
    private:
        std::string _name;
        std::string _address;
        std::shared_ptr<Protocol> _protocol;

        bool _test_is_running = false;
        std::chrono::_V2::system_clock::time_point _test_start;
        long _duration_ms = 0;
        std::string _status = "Idle";
        static const int kNanoSecondsToMilliseconds = 1000000;
        
    public:
        Connection(std::string name, std::string address, std::shared_ptr<Protocol> _protocol);
        //starts async test to see if the endpoint is reacheable
        //Ignored if called while another test is running
        void TestConnection();
        //returns the current status of the test or final results
        std::unique_ptr<ConnectionTestStatus> Status();
};

#endif