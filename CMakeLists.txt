cmake_minimum_required(VERSION 3.8)

project(Interpreter CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Threads REQUIRED)
find_package(fmt REQUIRED)
find_package(Readline REQUIRED)

add_subdirectory(source bin)
