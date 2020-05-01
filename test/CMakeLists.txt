set(TEST_SRC_LIST
    main.cpp
    tgbot/net/Url.cpp
    tgbot/net/HttpParser.cpp
    tgbot/tools/StringTools.cpp
)

include_directories("${PROJECT_SOURCE_DIR}/test")
add_executable(${PROJECT_NAME}_test ${TEST_SRC_LIST})
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
add_test(${PROJECT_NAME}_test ${PROJECT_NAME}_test)
