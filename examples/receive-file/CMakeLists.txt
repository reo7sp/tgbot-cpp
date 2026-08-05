cmake_minimum_required(VERSION 3.20)
project(receive-file LANGUAGES CXX)

find_package(TgBot CONFIG REQUIRED)

add_executable(receive-file src/main.cpp)
target_compile_features(receive-file PRIVATE cxx_std_20)
target_compile_options(receive-file PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall>
)
target_link_libraries(receive-file PRIVATE TgBot::TgBot)
install(TARGETS receive-file RUNTIME DESTINATION bin COMPONENT example)
