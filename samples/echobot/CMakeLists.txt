cmake_minimum_required(VERSION 3.10.2)
project(echobot)

include(../common_defs.cmake)
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(echobot ${LINK_LIB_LIST})
