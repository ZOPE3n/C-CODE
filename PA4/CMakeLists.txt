cmake_minimum_required(VERSION 3.8)
project(PA4)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c " Graph.h")
add_executable(PA4 ${SOURCE_FILES})