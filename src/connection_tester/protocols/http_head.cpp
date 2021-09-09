#include "connection_tester/protocols/http_head.h"

HttpHead::HttpHead() : Protocol("TCP"){};

void ConnectToHost(
    const boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp>& resolved_addresses,
    std::shared_ptr<boost::beast::tcp_stream> stream,
    std::shared_ptr<std::condition_variable> connect_condition,
    bool& timed_out){

    if(resolved_addresses.end() != resolved_addresses){
        stream->connect(resolved_addresses);  
    }
    timed_out = false;
    connect_condition->notify_all();
}

std::string HttpHead::TestConnection(std::string address){

    std::string host = address.substr(0, address.find_first_of(":"));
    std::string port = address.substr(address.find_first_of(":")+1);

    std::chrono::seconds timeout(5);
    
    auto connect_condition = std::make_shared<std::condition_variable>();
    std::mutex connect_mutex;
    std::unique_lock<std::mutex> connect_lock(connect_mutex);

    boost::asio::io_context io_context;
    auto address_resolver = boost::asio::ip::tcp::resolver(io_context);
    auto stream = std::make_shared<boost::beast::tcp_stream>(io_context);

    try {
        bool timed_out = true;
        auto const resolved_addresses = address_resolver.resolve(host, port);
        std::thread connection_thread(ConnectToHost, resolved_addresses, stream, connect_condition, std::ref(timed_out));
        connection_thread.detach();
        connect_condition->wait_for(connect_lock, timeout);
        stream->close();
        if(timed_out)
            return "Timed Out";
    } catch (const boost::system::system_error& exception){
        return exception.what();
    }
    return "OK";
}