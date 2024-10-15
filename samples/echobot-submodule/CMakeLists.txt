cmake_minimum_required(VERSION 3.10.2)
project(echobot-submodule)

include(../common_defs.cmake)
add_subdirectory(tgbot-cpp)
add_executable(echobot-submodule src/main.cpp)
target_link_libraries(echobot-submodule TgBot ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES} JsonCpp::JsonCpp)
