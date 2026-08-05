cmake_minimum_required(VERSION 3.20)
project(echobot-webhook-server LANGUAGES CXX)

find_package(TgBot CONFIG REQUIRED)

add_executable(echobot-webhook-server src/main.cpp)
target_compile_features(echobot-webhook-server PRIVATE cxx_std_20)
target_compile_options(echobot-webhook-server PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall>
)
target_link_libraries(echobot-webhook-server PRIVATE TgBot::TgBot)
install(TARGETS echobot-webhook-server RUNTIME DESTINATION bin)
