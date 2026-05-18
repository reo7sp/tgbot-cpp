#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>

#include "maxbot/net/HttpClient.h"
#include "maxbot/Api.h"
#include "maxbot/BotException.h"

using namespace std;
using namespace MaxBot;

typedef BotException::ErrorCode BotErrorCode;

class TestableApi : public Api {
public:
    using Api::Api;
    using Api::sendRequest;
};

class HttpClientMock : public HttpClient {
public:
    std::string makeRequest(const Url& url, const std::vector<HttpReqArg>& args) const override 
    {return response;};

    int getRequestMaxRetries() const override { return 0;};
    int getRequestBackoff() const override {return 1;};

    string response;
};

bool Request(BotErrorCode expectedCode, const string& response) {
    HttpClientMock httpClientMock;
    httpClientMock.response = response;

    TestableApi api("token", httpClientMock, "url");

    try {
        api.sendRequest("", vector<HttpReqArg>());
    } catch (BotException& exception) {
        return exception.errorCode == expectedCode;
    }

    return false;
}

BOOST_AUTO_TEST_SUITE(tApi)

BOOST_AUTO_TEST_CASE(sendRequest) {
    BOOST_CHECK(Request(BotErrorCode::HtmlResponse, "<html>"));
    BOOST_CHECK(Request(BotErrorCode::Undefined, "{\"ok\": false}"));
    BOOST_CHECK(Request(BotErrorCode::Undefined, "{\"ok\": false, \"error_code\":0}"));

    BOOST_CHECK(Request(BotErrorCode::BadRequest, "{\"ok\": false, \"error_code\":400}"));
    BOOST_CHECK(Request(BotErrorCode::Unauthorized, "{\"ok\": false, \"error_code\":401}"));
    BOOST_CHECK(Request(BotErrorCode::Forbidden, "{\"ok\": false, \"error_code\":403}"));
    BOOST_CHECK(Request(BotErrorCode::NotFound, "{\"ok\": false, \"error_code\":404}"));
    BOOST_CHECK(Request(BotErrorCode::Flood, "{\"ok\": false, \"error_code\":402}"));
    BOOST_CHECK(Request(BotErrorCode::Internal, "{\"ok\": false, \"error_code\":500}"));

    BOOST_CHECK(Request(BotErrorCode::InvalidJson, "error_code:101"));
}

BOOST_AUTO_TEST_SUITE_END()
