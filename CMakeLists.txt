cmake_minimum_required(VERSION 2.8.4)
project(TgBot)

### options
option(ENABLE_TESTS "Set to ON to enable building of tests" OFF)

### sources
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
include_directories(include)
set(SRC_LIST
	src/Api.cpp
	src/TgTypeParser.cpp
	src/TgException.cpp
	src/EventHandler.cpp
	src/net/Url.cpp
	src/net/HttpClient.cpp
	src/net/HttpParser.cpp
	src/net/TgLongPoll.cpp
	src/tools/StringTools.cpp
	src/tools/FileTools.cpp
	src/types/InlineQueryResult.cpp
	src/types/InputFile.cpp
)

### libs
# threads
find_package(Threads REQUIRED)

# openssl
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# boost
set(Boost_USE_MULTITHREADED ON)
if (ENABLE_TESTS)
	find_package(Boost 1.59.0 COMPONENTS system iostreams unit_test_framework REQUIRED)
else()
	find_package(Boost 1.59.0 COMPONENTS system iostreams REQUIRED)
endif()
include_directories(${Boost_INCLUDE_DIR})

set(LIB_LIST
	${CMAKE_THREAD_LIBS_INIT}
	${OPENSSL_LIBRARIES}
	${Boost_LIBRARIES}
)

### building project
add_library(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${LIB_LIST})
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

### tests
if (ENABLE_TESTS)
	message(STATUS "Building of tests is enabled")
	enable_testing()
	add_subdirectory(test)
endif()
