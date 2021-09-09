#ifndef _CONNECTION_TESTER_CONNECTION_TEST_STATUS_H_
#define _CONNECTION_TESTER_CONNECTION_TEST_STATUS_H_

#include <string>

struct ConnectionTestStatus {
    std::string name;
    std::string protocol_name;
    //holds status, or if the test is complete the test results
    std::string status = "Not Started";
    int duration_ms = 0;

    bool test_is_complete = false;
};

#endif