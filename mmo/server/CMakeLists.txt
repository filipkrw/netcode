cmake_minimum_required(VERSION 3.26)

project(MMOServer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

include_directories(lib/asio net_common mmo/common)
file(GLOB_RECURSE SOURCES *.cpp)

add_executable(MMOServer ${SOURCES})

if(MINGW)
  target_link_libraries(MMOServer ws2_32 wsock32)
endif()