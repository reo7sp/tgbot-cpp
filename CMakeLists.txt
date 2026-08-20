cmake_minimum_required(VERSION 3.16)
project(TgBot LANGUAGES CXX)

option(ENABLE_TESTS "Build tests" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_DOCUMENTATION "Build API documentation" OFF)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

find_package(Boost 1.65.1 REQUIRED)
find_package(CURL 7.58.0 REQUIRED)
find_package(nlohmann_json 3.7.3 REQUIRED)
find_package(Threads REQUIRED)

add_library(TgBot
    src/Api.cpp
    src/ApiCodec.cpp
    src/ApiMethods.cpp
    src/Bot.cpp
    src/EventBroadcaster.cpp
    src/EventHandler.cpp
    src/HttpClient.cpp
    src/TgException.cpp
    src/CurlHttpClient.cpp
    src/TgLongPoll.cpp
    src/TgWebhookLocalServer.cpp
    src/TgWebhookTcpServer.cpp
    src/InputFile.cpp
    src/Types.cpp
)
add_library(TgBot::TgBot ALIAS TgBot)

set_source_files_properties(src/Types.cpp PROPERTIES
    COMPILE_OPTIONS "$<$<CXX_COMPILER_ID:MSVC>:/bigobj>"
)

target_compile_features(TgBot PUBLIC cxx_std_20)
target_compile_options(TgBot PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall>
)
target_include_directories(TgBot PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(TgBot PUBLIC
    Boost::headers
    CURL::libcurl
    nlohmann_json::nlohmann_json
    Threads::Threads
)
set_target_properties(TgBot PROPERTIES
    CXX_EXTENSIONS OFF
)

if(BUILD_SHARED_LIBS)
    target_compile_definitions(TgBot PUBLIC TGBOT_DLL)
endif()

if(WIN32)
    target_compile_definitions(TgBot PUBLIC
        _WIN32_WINNT=0x0601
        WIN32_LEAN_AND_MEAN
        NOMINMAX
    )
    target_link_libraries(TgBot PRIVATE Ws2_32)
endif()

install(TARGETS TgBot
    EXPORT TgBotTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(TGBOT_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/TgBot")
configure_package_config_file(
    cmake/TgBotConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/TgBotConfig.cmake"
    INSTALL_DESTINATION "${TGBOT_INSTALL_CMAKEDIR}"
)
install(EXPORT TgBotTargets
    NAMESPACE TgBot::
    FILE TgBotTargets.cmake
    DESTINATION "${TGBOT_INSTALL_CMAKEDIR}"
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/TgBotConfig.cmake"
    DESTINATION "${TGBOT_INSTALL_CMAKEDIR}"
)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_DOCUMENTATION)
    find_package(Doxygen REQUIRED)
    add_custom_target(doc_doxygen ALL
        COMMAND Doxygen::doxygen ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc/html/
        DESTINATION ${CMAKE_INSTALL_DOCDIR}
    )
endif()
