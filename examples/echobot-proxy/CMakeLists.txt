cmake_minimum_required(VERSION 3.20)
project(echobot-proxy LANGUAGES CXX)

find_package(TgBot CONFIG REQUIRED)

add_executable(echobot-proxy src/main.cpp)
target_compile_features(echobot-proxy PRIVATE cxx_std_20)
target_compile_options(echobot-proxy PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall>
)
target_link_libraries(echobot-proxy PRIVATE TgBot::TgBot)
install(TARGETS echobot-proxy RUNTIME DESTINATION bin)
