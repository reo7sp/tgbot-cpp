find_package(GTest REQUIRED)

add_executable(TgBot_test
    tgbot/Api.cpp
    tgbot/CurlHttpClient.cpp
    tgbot/EventHandler.cpp
    tgbot/HttpFormField.cpp
    tgbot/HttpServer.cpp
    tgbot/TgLongPoll.cpp
    tgbot/TgWebhookServer.cpp
    tgbot/TypesJson.cpp
)
target_link_libraries(TgBot_test PRIVATE TgBot::TgBot GTest::gtest_main)
if(ENABLE_COVERAGE)
    target_compile_options(TgBot_test PRIVATE -O0 -g --coverage)
    target_link_options(TgBot_test PRIVATE --coverage)
endif()

include(GoogleTest)
gtest_discover_tests(TgBot_test)
