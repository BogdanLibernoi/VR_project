cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

set(PROJECT_NAME OpenVR)

project (${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.cpp)