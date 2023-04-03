cmake_minimum_required(VERSION 3.10.2)
project(TgBot)

if(POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW) # find_package() uses <PackageName>_ROOT variables
endif()

# options
option(ENABLE_TESTS "Set to ON to enable building of tests" OFF)
option(BUILD_SHARED_LIBS "Build tgbot-cpp shared/static library." OFF)
option(BUILD_DOCUMENTATION "Build doxygen API documentation." OFF)

# sources
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_definitions(-D_WIN32_WINNT=0x0601)
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-DNOMINMAX)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

include_directories(include)
set(SRC_LIST
    src/Api.cpp
    src/Bot.cpp
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
    src/types/BotCommandScope.cpp
    src/types/ChatMember.cpp
    src/types/InlineQueryResult.cpp
    src/types/InputFile.cpp
    src/types/InputMedia.cpp 
    src/types/InputMessageContent.cpp
    src/types/MenuButton.cpp
    src/types/PassportElementError.cpp)

# libs
## threads
find_package(Threads REQUIRED)

## zlib
find_package(ZLIB REQUIRED)

## openssl
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

## curl
find_package(CURL 7.58.0)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

## boost
set(Boost_USE_MULTITHREADED ON)
if (ENABLE_TESTS)
    find_package(Boost 1.65.1 COMPONENTS system unit_test_framework REQUIRED)
else()
    find_package(Boost 1.65.1 COMPONENTS system REQUIRED)
endif()
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR_RELEASE})
if(NOT Boost_USE_STATIC_LIBS)
    add_definitions(-DBOOST_ALL_DYN_LINK)
endif()

set(LIB_LIST
    ${CMAKE_THREAD_LIBS_INIT}
    ${ZLIB_LIBRARIES}
    ${OPENSSL_LIBRARIES}
    ${Boost_LIBRARIES}
)

if (CURL_FOUND)
    set(LIB_LIST ${LIB_LIST} ${CURL_LIBRARIES})
endif()

# building project
add_library(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} ${LIB_LIST})
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# ABI version
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION 1)

# tests
if (ENABLE_TESTS)
    message(STATUS "Building of tests is enabled")
    enable_testing()
    add_subdirectory(test)
endif()

# Documentation
if(BUILD_DOCUMENTATION)
    find_package(Doxygen REQUIRED)
    add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
        install(DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/doc/html/ TYPE DOC)
endif()

if(BUILD_SHARED_LIBS)
    add_definitions(-DTGBOT_DLL)
endif()
