cmake_minimum_required(VERSION 3.26)

project(NetClient)

set(CMAKE_CXX_STANDARD 14)

include_directories("${PROJECT_SOURCE_DIR}/lib")

file(GLOB_RECURSE SOURCES *.cpp)

add_executable(NetClient ${SOURCES})