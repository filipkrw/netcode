cmake_minimum_required(VERSION 3.26)

project(NetClient)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

include_directories(lib/asio net_common)
file(GLOB_RECURSE SOURCES *.cpp)

add_executable(NetClient ${SOURCES})

if(MINGW)
  target_link_libraries(NetClient ws2_32)
endif()