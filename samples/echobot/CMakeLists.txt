set(SAMPLE_NAME echobot)

add_executable(${SAMPLE_NAME} src/main.cpp)
target_link_libraries(${SAMPLE_NAME} TgBot)