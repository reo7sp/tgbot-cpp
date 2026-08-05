cmake_minimum_required(VERSION 3.20)
project(echobot LANGUAGES CXX)

find_package(TgBot CONFIG REQUIRED)

add_executable(echobot src/main.cpp)
target_compile_features(echobot PRIVATE cxx_std_20)
target_compile_options(echobot PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall>
)
target_link_libraries(echobot PRIVATE TgBot::TgBot)
install(TARGETS echobot RUNTIME DESTINATION bin COMPONENT example)
