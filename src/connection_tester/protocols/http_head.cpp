#include "connection_tester/protocols/http_head.h"

HttpHead::HttpHead() : Protocol("HTTP/HEAD"){};

std::string HttpHead::TestConnection(std::string address){
    return "200 OK";
}