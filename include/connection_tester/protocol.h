#ifndef _CONNECTION_TESTER_PROTOCOL_H_
#define _CONNECTION_TESTER_PROTOCOL_H_

#include <vector>
#include <string>
#include <memory>

class Protocol {
    private:
        std::string _name;
    public:
        Protocol(std::string name);
        std::string Name();
        virtual std::string TestConnection(std::string address) = 0;
};

#endif