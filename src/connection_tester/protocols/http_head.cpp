#include "connection_tester/protocols/http_head.h"

HttpHead::HttpHead() : Protocol("HTTP/HEAD"){};

std::string HttpHead::TestConnection(std::string address){

    // boost::asio::io_context io_context;
    // auto address_resolver = boost::asio::ip::tcp::resolver(io_context);
    // boost::beast::tcp_stream stream(io_context);

    // auto const results = address_resolver.resolve("www.google.com", "http");
    // //check destination can be contacted and prepairs the stream
    // if(results.end() != results)
    //     stream.connect(results);
    // stream.close();

    return "OK";
}