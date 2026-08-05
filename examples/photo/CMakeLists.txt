cmake_minimum_required(VERSION 3.20)
project(photo LANGUAGES CXX)

find_package(TgBot CONFIG REQUIRED)

add_executable(photo src/main.cpp)
target_compile_features(photo PRIVATE cxx_std_20)
target_compile_options(photo PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall>
)
target_link_libraries(photo PRIVATE TgBot::TgBot)
install(TARGETS photo RUNTIME DESTINATION bin)
