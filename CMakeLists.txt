cmake_minimum_required(VERSION 3.26)

project(Netcode)

set(CMAKE_CXX_STANDARD 14)

include_directories("${PROJECT_SOURCE_DIR}/lib/asio/include"
                    "${PROJECT_SOURCE_DIR}/lib")

file(GLOB_RECURSE SOURCES src/*.cpp)

add_subdirectory(net_client)

add_executable(NetCode ${SOURCES})