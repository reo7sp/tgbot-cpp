#include <boost/test/unit_test.hpp>

#include <tgbot/net/Url.h>

using namespace TgBot;

BOOST_AUTO_TEST_SUITE(tUrl)

BOOST_AUTO_TEST_CASE(parsingUrlNoPath) {
    Url t("https://test.example.com?test=123&123=test#title");
    BOOST_CHECK_EQUAL(t.protocol, "https");
    BOOST_CHECK_EQUAL(t.host, "test.example.com");
    BOOST_CHECK_EQUAL(t.path, "/");
    BOOST_CHECK_EQUAL(t.query, "test=123&123=test");
    BOOST_CHECK_EQUAL(t.fragment, "title");
}

BOOST_AUTO_TEST_CASE(parsingUrlNoPathAndQuery) {
    Url t("https://test.example.com#title");
    BOOST_CHECK_EQUAL(t.protocol, "https");
    BOOST_CHECK_EQUAL(t.host, "test.example.com");
    BOOST_CHECK_EQUAL(t.path, "/");
    BOOST_CHECK_EQUAL(t.query, "");
    BOOST_CHECK_EQUAL(t.fragment, "title");
}

BOOST_AUTO_TEST_CASE(parsingUrlFull) {
    Url t("https://test.example.com/example-page/index.html?test=123&123=test#title");
    BOOST_CHECK_EQUAL(t.protocol, "https");
    BOOST_CHECK_EQUAL(t.host, "test.example.com");
    BOOST_CHECK_EQUAL(t.path, "/example-page/index.html");
    BOOST_CHECK_EQUAL(t.query, "test=123&123=test");
    BOOST_CHECK_EQUAL(t.fragment, "title");
}

BOOST_AUTO_TEST_SUITE_END()
