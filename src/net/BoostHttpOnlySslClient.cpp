#include "tgbot/net/BoostHttpOnlySslClient.h"

#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>

#include <cstddef>
#include <vector>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::placeholders;

namespace TgBot {

template<typename IoContext>
class BoostAsioSslClient {
private:
    void on_completion1(const boost::system::error_code& ec) {
        ec_ = ec;

#if BOOST_VERSION < 106600
        io_context_.stop(); // Notify io that opertion is completed
#endif // BOOST_VERSION < 106600
    }

    void on_completion2(const boost::system::error_code& ec, std::size_t bytes_transferred) {
        ec_ = ec;
        bytes_transferred_ = bytes_transferred;

#if BOOST_VERSION < 106600
        io_context_.stop(); // Notify io that opertion is completed
#endif // BOOST_VERSION < 106600
    }

    IoContext& io_context_;
    boost::system::error_code ec_{};
    std::size_t bytes_transferred_ = 0;

    std::size_t io_run_for(boost::asio::chrono::steady_clock::duration timeout) {
#if BOOST_VERSION >= 108700
        io_context_.restart();
#else // BOOST_VERSION >= 108700
        io_context_.reset();
#endif // BOOST_VERSION >= 108700

#if BOOST_VERSION < 106600
        boost::asio::steady_timer timer(io_context_);
        timer.expires_from_now(dur);

        bool timed_out = false;
        timer.async_wait([&](const boost::system::error_code& ec) {
            if (!ec) { // not cancelled => deadline hit
                timed_out = true;
                io_context_.stop(); // unblocks run()
            }
        });

        std::size_t n = io_context_.run();

        if (!timed_out)
            timer.cancel(); // Stream is alive. Abort timer
        else
            socket.lowest_layer().close();

        io_context_.reset();
        io_context_.run(); // drain the cancellation handlers

        return n;
#else // BOOST_VERSION < 106600
        std::size_t n = io_context_.run_for(timeout);

        if (!io_context_.stopped()) {
            socket.lowest_layer().close();
            io_context_.run(); // drain the socket operation
        }

        return n;
#endif // BOOST_VERSION < 106600
    }

    // Return true if operation is completed for specified time range, false otherwase
    bool do_process_for(boost::asio::chrono::steady_clock::duration timeout) {
        // Custom io_context.run_for using legacy io_service can return > 0 on timer out  
#if BOOST_VERSION < 106600
        return io_run_for(timeout) > 0 && ec_ != error::operation_aborted;
#else // BOOST_VERSION < 106600
        return io_run_for(timeout) > 0;
#endif // BOOST_VERSION < 106600
    }

public:
    explicit BoostAsioSslClient(IoContext& io_context, ssl::context& ssl_context) 
     : io_context_(io_context), resolver(io_context), socket(io_context, ssl_context)
    {}

    boost::system::error_code connect(const Url& url, boost::asio::chrono::steady_clock::duration timeout) {
#if BOOST_VERSION >= 108700
        async_connect(socket.lowest_layer(), resolver.resolve(url.host, "443"), 
            boost::bind(&BoostAsioSslClient::on_completion1, this, _1));
#else // BOOST_VERSION >= 108700
        tcp::resolver::query query(url.host, "443");
        async_connect(socket.lowest_layer(), resolver.resolve(query),
            boost::bind(&BoostAsioSslClient::on_completion1, this, _1));
#endif // BOOST_VERSION >= 108700

        if(do_process_for(timeout))
            return ec_;

        return boost::system::errc::make_error_code(boost::system::errc::timed_out);
    }

    boost::system::error_code handshake(boost::asio::chrono::steady_clock::duration timeout) {
        socket.async_handshake(boost::asio::ssl::stream_base::client,
            boost::bind(&BoostAsioSslClient::on_completion1, this, _1));

        if(do_process_for(timeout))
            return ec_;

        return boost::system::errc::make_error_code(boost::system::errc::timed_out);
    }

    std::size_t write(boost::asio::chrono::steady_clock::duration timeout, const_buffer buffer, 
        boost::system::error_code& ec) {
        boost::asio::async_write(socket, buffer,
            boost::bind(&BoostAsioSslClient::on_completion2, this, _1, _2));

        ec = boost::system::errc::make_error_code(boost::system::errc::timed_out);
        if(do_process_for(timeout))
            ec = ec_;

        return bytes_transferred_;
    }

    std::size_t read(boost::asio::chrono::steady_clock::duration timeout, mutable_buffer buffer, 
        boost::system::error_code& ec) {
        boost::asio::async_read(socket, buffer,
            boost::bind(&BoostAsioSslClient::on_completion2, this, _1, _2));

        ec = boost::system::errc::make_error_code(boost::system::errc::timed_out);
        if(do_process_for(timeout))
            ec = ec_;

        return bytes_transferred_;
    }

    tcp::resolver resolver;
    ssl::stream<tcp::socket> socket;
};

BoostHttpOnlySslClient::BoostHttpOnlySslClient() : _httpParser() {
}

BoostHttpOnlySslClient::~BoostHttpOnlySslClient() {
}

string BoostHttpOnlySslClient::makeRequest(const Url& url, const vector<HttpReqArg>& args) const {
    boost::system::error_code current_ec;
    ssl::context context(ssl::context::tlsv12_client);
    BoostAsioSslClient client_ssl(_ioService, context);
    context.set_default_verify_paths();

    boost::asio::chrono::steady_clock::duration rw_duration 
        = boost::asio::chrono::seconds(_timeout <= 0 ? 0 : _timeout);
    boost::asio::chrono::steady_clock::duration conn_duration
        = rw_duration / 2;

    if((current_ec = client_ssl.connect(url, conn_duration)))
        throw boost::system::system_error(current_ec, "Client SSL connect failed");

#ifdef TGBOT_DISABLE_NAGLES_ALGORITHM
    client_ssl.socket.lowest_layer().set_option(tcp::no_delay(true));
#endif //TGBOT_DISABLE_NAGLES_ALGORITHM
#ifdef TGBOT_CHANGE_SOCKET_BUFFER_SIZE
    #if _WIN64 || __amd64__ || __x86_64__ || __MINGW64__ || __aarch64__ || __powerpc64__
    client_ssl.socket.lowest_layer().set_option(socket_base::send_buffer_size(65536));
    client_ssl.socket.lowest_layer().set_option(socket_base::receive_buffer_size(65536));
    #else //for 32-bit
    client_ssl.socket.lowest_layer().set_option(socket_base::send_buffer_size(32768));
    client_ssl.socket.lowest_layer().set_option(socket_base::receive_buffer_size(32768));
    #endif //Processor architecture
#endif //TGBOT_CHANGE_SOCKET_BUFFER_SIZE
    client_ssl.socket.set_verify_mode(ssl::verify_none);
#if BOOST_VERSION >= 108700
    client_ssl.socket.set_verify_callback(ssl::host_name_verification(url.host));
#else // BOOST_VERSION >= 108700
    client_ssl.socket.set_verify_callback(ssl::rfc2818_verification(url.host));
#endif // BOOST_VERSION >= 108700

    if((current_ec = client_ssl.handshake(conn_duration)))
        throw boost::system::system_error(current_ec, "Client SSL handshake failed");

    string requestText = _httpParser.generateRequest(url, args, false);
    std::size_t bytes_transferred = client_ssl.write(rw_duration, 
        buffer(requestText.c_str(), requestText.length()), current_ec);
    if(current_ec)
        throw boost::system::system_error(current_ec, "Client SSL send failed");
    BOOST_ASSERT(bytes_transferred == requestText.size());
    
    string response;

#ifdef TGBOT_CHANGE_READ_BUFFER_SIZE
    #if _WIN64 || __amd64__ || __x86_64__ || __MINGW64__ || __aarch64__ || __powerpc64__
    char buff[65536];
    #else //for 32-bit
    char buff[32768];
    #endif //Processor architecture
#else //TGBOT_CHANGE_READ_BUFFER_SIZE
    char buff[1024];
#endif //TGBOT_CHANGE_READ_BUFFER_SIZE

    while (!current_ec) {
        std::size_t bytes = client_ssl.read(rw_duration, buffer(buff), current_ec);
        response += string(buff, bytes);
    }

    // Server must send EOF because a request formed with "Connection: close"
    if(current_ec && current_ec != boost::asio::error::eof)
        throw boost::system::system_error(current_ec, "Client SSL recv failed");

    return _httpParser.extractBody(response);
}

}
