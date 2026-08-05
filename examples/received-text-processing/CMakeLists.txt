cmake_minimum_required(VERSION 3.20)
project(received-text-processing LANGUAGES CXX)

find_package(TgBot CONFIG REQUIRED)

add_executable(received-processing-text src/main.cpp)
target_compile_features(received-processing-text PRIVATE cxx_std_20)
target_compile_options(received-processing-text PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall>
)
target_link_libraries(received-processing-text PRIVATE TgBot::TgBot)
install(TARGETS received-processing-text RUNTIME DESTINATION bin)
