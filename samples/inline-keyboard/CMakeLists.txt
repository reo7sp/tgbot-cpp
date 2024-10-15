cmake_minimum_required(VERSION 3.10.2)
project(inline-keyboard)

include(../common_defs.cmake)
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${LINK_LIB_LIST})
