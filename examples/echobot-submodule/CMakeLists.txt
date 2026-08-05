cmake_minimum_required(VERSION 3.20)
project(echobot-submodule LANGUAGES CXX)

set(TGBOT_CPP_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tgbot-cpp" CACHE PATH "Path to tgbot-cpp sources")
add_subdirectory("${TGBOT_CPP_SOURCE_DIR}" tgbot-cpp-build)
add_executable(echobot-submodule src/main.cpp)
target_compile_features(echobot-submodule PRIVATE cxx_std_20)
target_compile_options(echobot-submodule PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall>
)
target_link_libraries(echobot-submodule PRIVATE TgBot::TgBot)
install(TARGETS echobot-submodule RUNTIME DESTINATION bin COMPONENT example)
