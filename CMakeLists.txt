cmake_minimum_required(VERSION 3.26)

project(Netcode)

set(CMAKE_CXX_STANDARD 11)

include_directories("${PROJECT_SOURCE_DIR}/lib/asio/include")

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(Netcode ${SOURCES})