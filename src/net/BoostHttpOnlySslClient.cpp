#include "tgbot/net/BoostHttpOnlySslClient.h"

#include <boost/asio/ssl.hpp>

#include <cstddef>
#include <vector>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace TgBot {

BoostHttpOnlySslClient::BoostHttpOnlySslClient() : _httpParser() {
}

BoostHttpOnlySslClient::~BoostHttpOnlySslClient() {
}

string BoostHttpOnlySslClient::makeRequest(const Url& url, const vector<HttpReqArg>& args) const {
    tcp::resolver resolver(_ioService);

    ssl::context context(ssl::context::tlsv12_client);
    context.set_default_verify_paths();

    ssl::stream<tcp::socket> socket(_ioService, context);
#if BOOST_VERSION >= 108700
    connect(socket.lowest_layer(), resolver.resolve(url.host, "443"));
#else
    tcp::resolver::query query(url.host, "443");
    connect(socket.lowest_layer(), resolver.resolve(query));
#endif

    #ifdef TGBOT_DISABLE_NAGLES_ALGORITHM
    socket.lowest_layer().set_option(tcp::no_delay(true));
    #endif //TGBOT_DISABLE_NAGLES_ALGORITHM
    #ifdef TGBOT_CHANGE_SOCKET_BUFFER_SIZE
    #if _WIN64 || __amd64__ || __x86_64__ || __MINGW64__ || __aarch64__ || __powerpc64__
    socket.lowest_layer().set_option(socket_base::send_buffer_size(65536));
    socket.lowest_layer().set_option(socket_base::receive_buffer_size(65536));
    #else //for 32-bit
    socket.lowest_layer().set_option(socket_base::send_buffer_size(32768));
    socket.lowest_layer().set_option(socket_base::receive_buffer_size(32768));
    #endif //Processor architecture
    #endif //TGBOT_CHANGE_SOCKET_BUFFER_SIZE
    socket.set_verify_mode(ssl::verify_none);
#if BOOST_VERSION >= 108700
    socket.set_verify_callback(ssl::host_name_verification(url.host));
#else
    socket.set_verify_callback(ssl::rfc2818_verification(url.host));
#endif

    socket.handshake(ssl::stream<tcp::socket>::client);

    string requestText = _httpParser.generateRequest(url, args, false);
    write(socket, buffer(requestText.c_str(), requestText.length()));

    fd_set fileDescriptorSet;
    struct timeval timeStruct;
    
    // set the timeout to 20 seconds
    timeStruct.tv_sec = _timeout;
    timeStruct.tv_usec = 0;
    FD_ZERO(&fileDescriptorSet);
    
    // We'll need to get the underlying native socket for this select call, in order
    // to add a simple timeout on the read:
    
    int nativeSocket = static_cast<int>(socket.lowest_layer().native_handle());
    
    FD_SET(nativeSocket,&fileDescriptorSet);        
    select(nativeSocket+1,&fileDescriptorSet,NULL,NULL,&timeStruct);
    
    if(!FD_ISSET(nativeSocket,&fileDescriptorSet)){ // timeout
        
        std::string sMsg("TIMEOUT on read client data. Client IP: ");
        
        sMsg.append(socket.next_layer().remote_endpoint().address().to_string());
    #if BOOST_VERSION >= 108700
        _ioService.restart();
    #else
        _ioService.reset();
    #endif
        
        throw std::exception();
    }      
    
    string response;

    #ifdef TGBOT_CHANGE_READ_BUFFER_SIZE
    #if _WIN64 || __amd64__ || __x86_64__ || __MINGW64__ || __aarch64__ || __powerpc64__
    char buff[65536];
    #else //for 32-bit
    char buff[32768];
    #endif //Processor architecture
    #else
    char buff[1024];
    #endif //TGBOT_CHANGE_READ_BUFFER_SIZE

    boost::system::error_code error;
    while (!error) {
        std::size_t bytes = read(socket, buffer(buff), error);
        response += string(buff, bytes);
    }

    return _httpParser.extractBody(response);
}

}
