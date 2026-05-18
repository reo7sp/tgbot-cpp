set(TEST_SRC_LIST
    main.cpp
    maxbot/Api.cpp
    maxbot/net/Url.cpp
    maxbot/net/HttpParser.cpp
    maxbot/tools/StringTools.cpp
)

include_directories("${PROJECT_SOURCE_DIR}/test")
add_executable(${PROJECT_NAME}_test ${TEST_SRC_LIST})
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
add_test(${PROJECT_NAME}_test ${PROJECT_NAME}_test)
