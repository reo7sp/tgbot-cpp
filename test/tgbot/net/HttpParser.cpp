#include <boost/test/unit_test.hpp>

#include <tgbot/net/HttpParser.h>

#include "utils.h"

using namespace std;
using namespace TgBot;

BOOST_AUTO_TEST_SUITE(tHttpParser)

BOOST_AUTO_TEST_CASE(generateRequest) {
    vector<HttpReqArg> args = { HttpReqArg("email", "test@example.com"), HttpReqArg("text", "Hello, world!") };
    string t = HttpParser().generateRequest(Url("http://example.com/index.html"), args, true);
    string e = ""
        "POST /index.html HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "Connection: keep-alive\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "Content-Length: 49\r\n"
        "\r\n"
        "email=test%40example.com&text=Hello%2C%20world%21";
    BOOST_CHECK_MESSAGE(t == e, diffS(t, e));
}

BOOST_AUTO_TEST_CASE(generateMultipartFormData) {
    vector<HttpReqArg> args = { HttpReqArg("email", "test@example.com"), HttpReqArg("text", "Hello, world!", true) };
    string boundary = HttpParser().generateMultipartBoundary(args);
    string t = HttpParser().generateMultipartFormData(args, boundary);
    string e = ""
        "--" + boundary + "\r\n"
        "Content-Disposition: form-data; name=\"email\"\r\n"
        "\r\n"
        "test@example.com\r\n"
        "--" + boundary + "\r\n"
        "Content-Disposition: form-data; name=\"text\"; filename=\"\"\r\n"
        "Content-Type: text/plain\r\n"
        "\r\n"
        "Hello, world!\r\n"
        "--" + boundary + "--\r\n";
    BOOST_CHECK_MESSAGE(t == e, diffS(t, e));
}

BOOST_AUTO_TEST_CASE(generateWwwFormUrlencoded) {
    vector<HttpReqArg> args = { HttpReqArg("email", "test@example.com"), HttpReqArg("text", "Hello, world!") };
    string t = HttpParser().generateWwwFormUrlencoded(args);
    string e = "email=test%40example.com&text=Hello%2C%20world%21";
    BOOST_CHECK_MESSAGE(t == e, diffS(t, e));
}

BOOST_AUTO_TEST_CASE(generateResponse) {
    string t = HttpParser().generateResponse("testdata", "text/plain", 200, "OK", false);
    string e = ""
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 8\r\n"
        "Connection: close\r\n"
        "\r\n"
        "testdata";
    BOOST_CHECK_MESSAGE(t == e, diffS(t, e));
}

BOOST_AUTO_TEST_CASE(parseRequest) {
    string data = ""
        "POST /index.html HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "Connection: keep-alive\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 8\r\n"
        "\r\n"
        "testdata";

    unordered_map<string, string> tHeaders = HttpParser().parseHeader(data.substr(0, data.rfind("\r\n")), true);
    string tBody = HttpParser().extractBody(data);

    unordered_map<string, string> eHeaders = {
        { "_method", "POST" },
        { "_path", "/index.html" },
        { "Host", "example.com" },
        { "Connection", "keep-alive" },
        { "Content-Type", "text/plain" },
        { "Content-Length", "8" }
    };
    string eBody = "testdata";

    BOOST_CHECK_MESSAGE(tBody == eBody, diffS(tBody, eBody));
    BOOST_CHECK_MESSAGE(tHeaders == eHeaders, diffMSS(tHeaders, eHeaders));
}

BOOST_AUTO_TEST_CASE(parseResponse) {
    string data = ""
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 8\r\n"
        "\r\n"
        "testdata";

    unordered_map<string, string> tHeaders = HttpParser().parseHeader(data.substr(0, data.rfind("\r\n")), false);
    string tBody = HttpParser().extractBody(data);

    unordered_map<string, string> eHeaders = {
        { "_status", "200" },
        { "Content-Type", "text/plain" },
        { "Content-Length", "8" }
    };
    string eBody = "testdata";

    BOOST_CHECK_MESSAGE(tBody == eBody, diffS(tBody, eBody));
    BOOST_CHECK_MESSAGE(tHeaders == eHeaders, diffMSS(tHeaders, eHeaders));
}

BOOST_AUTO_TEST_SUITE_END()
