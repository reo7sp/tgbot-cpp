cmake_minimum_required(VERSION 2.8.4)
project(TgBot)

### options
option(ENABLE_TESTS "Set to ON to enable building of tests" OFF)
option(ENABLE_SAMPLES "Set to ON to enable building of samples" OFF)

### sources
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories("${PROJECT_SOURCE_DIR}/include")
set(SRC_LIST
    src/tgbot/Api.cpp
    src/tgbot/TgTypeParser.cpp
    src/tgbot/TgException.cpp
    src/tgbot/net/Url.cpp
    src/tgbot/net/HttpClient.cpp
    src/tgbot/net/HttpParser.cpp
    src/tgbot/net/TgLongPoll.cpp
    src/tgbot/tools/StringTools.cpp
)

### libs
# openssl
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# boost
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS system iostreams unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(LIB_LIST
    ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES}
)

### building project
add_library(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${LIB_LIST})

### tests
if (ENABLE_TESTS)
    message(STATUS "Building of tests is enabled")
    enable_testing()
    add_subdirectory(test)
endif()

### samples
if (ENABLE_SAMPLES)
    message(STATUS "Building of sambles is enabled")
    add_subdirectory(samples)
endif()
