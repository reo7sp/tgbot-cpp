#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>

#include "tgbot/net/HttpClient.h"
#include "tgbot/Api.h"
#include "tgbot/TgException.h"

using namespace std;
using namespace TgBot;

typedef TgException::ErrorCode TgErrorCode;

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

bool Request(TgErrorCode expectedCode, const string& response) {
    HttpClientMock httpClientMock;
    httpClientMock.response = response;

    TestableApi api("token", httpClientMock, "url");

    try {
        api.sendRequest("", vector<HttpReqArg>());
    } catch (TgException& exception) {
        return exception.errorCode == expectedCode;
    }

    return false;
}

BOOST_AUTO_TEST_SUITE(tApi)

BOOST_AUTO_TEST_CASE(sendRequest) {
    BOOST_CHECK(Request(TgErrorCode::HtmlResponse, "<html>"));
    BOOST_CHECK(Request(TgErrorCode::Undefined, "{\"ok\": false}"));
    BOOST_CHECK(Request(TgErrorCode::Undefined, "{\"ok\": false, \"error_code\":0}"));

    BOOST_CHECK(Request(TgErrorCode::BadRequest, "{\"ok\": false, \"error_code\":400}"));
    BOOST_CHECK(Request(TgErrorCode::Unauthorized, "{\"ok\": false, \"error_code\":401}"));
    BOOST_CHECK(Request(TgErrorCode::Forbidden, "{\"ok\": false, \"error_code\":403}"));
    BOOST_CHECK(Request(TgErrorCode::NotFound, "{\"ok\": false, \"error_code\":404}"));
    BOOST_CHECK(Request(TgErrorCode::Flood, "{\"ok\": false, \"error_code\":402}"));
    BOOST_CHECK(Request(TgErrorCode::Internal, "{\"ok\": false, \"error_code\":500}"));

    BOOST_CHECK(Request(TgErrorCode::InvalidJson, "error_code:101"));
}

BOOST_AUTO_TEST_SUITE_END()
