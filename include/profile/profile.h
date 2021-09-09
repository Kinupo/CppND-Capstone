#ifndef _PROFILE_PROFILE_H_
#define _PROFILE_PROFILE_H_

struct ConnectionProfile{
    std::string name;
    std::string address;
    std::string protocal;
};

struct Profile{
    std::string name;
    std::vector<std::unique_ptr<ConnectionProfile>> connections;
};

#endif