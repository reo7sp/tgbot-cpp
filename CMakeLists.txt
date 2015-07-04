cmake_minimum_required(VERSION 3.0)
project(TgBot)

### options
option(ENABLE_TESTS "Set to ON to enable building of tests and samples" ON)

### sources
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories("${PROJECT_SOURCE_DIR}/src")
set(SRC_LIST
    src/tgbot/Bot.cpp
    src/tgbot/Api.cpp
    src/tgbot/EventManager.cpp
    src/tgbot/Http.cpp
    src/tgbot/Url.cpp
    src/tgbot/Parser.cpp
    src/tgbot/TgException.cpp
    src/tgbot/tools/StringTools.cpp
)

### libs
# openssl
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# boost
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS system container iostreams REQUIRED)
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
    message(STATUS "Building of tests and sambles is enabled")
    add_subdirectory(samples)
endif()
