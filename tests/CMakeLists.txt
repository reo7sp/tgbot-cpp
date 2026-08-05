find_package(GTest REQUIRED)

add_executable(TgBot_test
    tgbot/Api.cpp
    tgbot/EventHandler.cpp
    tgbot/HttpFormField.cpp
    tgbot/HttpServer.cpp
    tgbot/TgLongPoll.cpp
    tgbot/TypesJson.cpp
)
target_link_libraries(TgBot_test PRIVATE TgBot::TgBot GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(TgBot_test)
