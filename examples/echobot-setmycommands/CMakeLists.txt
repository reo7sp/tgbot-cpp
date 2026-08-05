cmake_minimum_required(VERSION 3.20)
project(echobot-setmycommands LANGUAGES CXX)

find_package(TgBot CONFIG REQUIRED)

add_executable(echobot-setmycommands src/main.cpp)
target_compile_features(echobot-setmycommands PRIVATE cxx_std_20)
target_compile_options(echobot-setmycommands PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall>
)
target_link_libraries(echobot-setmycommands PRIVATE TgBot::TgBot)
install(TARGETS echobot-setmycommands RUNTIME DESTINATION bin COMPONENT example)
