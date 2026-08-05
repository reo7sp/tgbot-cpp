cmake_minimum_required(VERSION 3.20)
project(inline-keyboard LANGUAGES CXX)

find_package(TgBot CONFIG REQUIRED)

add_executable(inline-keyboard src/main.cpp)
target_compile_features(inline-keyboard PRIVATE cxx_std_20)
target_compile_options(inline-keyboard PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall>
)
target_link_libraries(inline-keyboard PRIVATE TgBot::TgBot)
install(TARGETS inline-keyboard RUNTIME DESTINATION bin)
