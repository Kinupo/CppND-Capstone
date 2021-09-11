#include "connection_tester/protocols/tcp.h"

Tcp::Tcp() : Protocol("TCP"){};

void ConnectToHost(
    const boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp>& resolved_addresses,
    std::shared_ptr<boost::beast::tcp_stream> stream,
    std::promise<bool> timed_out_promise){

    if(resolved_addresses.end() != resolved_addresses){
        try{
            stream->connect(resolved_addresses);  
        } catch (const std::runtime_error& runtime_exception){
            //Ignore for now, this happens when the server does not respond but accepts the SYN 
            //this is protection from port scanning and SYN flood
        }
    }
}

std::string Tcp::TestConnection(std::string address){

    std::string host = address.substr(0, address.find_first_of(":"));
    std::string port = address.substr(address.find_first_of(":")+1);

    std::chrono::seconds timeout(5);

    boost::asio::io_context io_context;
    auto address_resolver = boost::asio::ip::tcp::resolver(io_context);
    auto stream = std::make_shared<boost::beast::tcp_stream>(io_context);

    try {
        std::promise<bool> timed_out_promise;
        auto timed_out_future = timed_out_promise.get_future();

        auto const resolved_addresses = address_resolver.resolve(host, port);
        std::thread connection_thread(
            ConnectToHost, 
            resolved_addresses, 
            stream, 
            std::move(timed_out_promise));
        connection_thread.detach();

        if(stream->socket().is_open());
            stream->socket().close();
        
        if(timed_out_future.valid() 
            && timed_out_future.wait_for(std::chrono::seconds(5)) == std::future_status::timeout)
            return "Timed Out";

    } catch (const boost::system::system_error& exception){
        return "Host not found";
    }
    return "OK";
}