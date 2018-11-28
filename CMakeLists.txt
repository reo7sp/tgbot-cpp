cmake_minimum_required(VERSION 2.8.4)
project(TgBot)

if (${CONAN_EXPORTED})
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# options
option(ENABLE_TESTS "Set to ON to enable building of tests" OFF)
option(BUILD_SHARED_LIBS "Build tgbot-cpp shared/static library." OFF)

# sources
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")  # Do not activate all warnings in VS (too much output for Appveyor)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
endif()

include_directories(include)
set(SRC_LIST
    src/Api.cpp
    src/EventHandler.cpp
    src/TgException.cpp
    src/TgTypeParser.cpp
    src/net/BoostHttpOnlySslClient.cpp
    src/net/CurlHttpClient.cpp
    src/net/HttpParser.cpp
    src/net/TgLongPoll.cpp
    src/net/Url.cpp
    src/tools/FileTools.cpp
    src/tools/StringTools.cpp
    src/types/InlineQueryResult.cpp
    src/types/InputFile.cpp
)

# libs
## threads
find_package(Threads REQUIRED)

# zlib
find_package(ZLIB REQUIRED)

## openssl
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

## curl
find_package(CURL)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

## boost
set(Boost_USE_MULTITHREADED ON)
if (ENABLE_TESTS)
    find_package(Boost 1.59.0 COMPONENTS system unit_test_framework REQUIRED)
else()
    find_package(Boost 1.59.0 COMPONENTS system REQUIRED)
endif()
include_directories(${Boost_INCLUDE_DIR})

set(LIB_LIST
    ${CMAKE_THREAD_LIBS_INIT}
    ${ZLIB_LIBRARIES}
    ${OPENSSL_LIBRARIES}
    ${Boost_LIBRARIES}
    ${CURL_LIBRARIES}
)

# building project
add_library(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} ${LIB_LIST})
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

# tests
if (ENABLE_TESTS)
    message(STATUS "Building of tests is enabled")
    enable_testing()
    add_subdirectory(test)
endif()
