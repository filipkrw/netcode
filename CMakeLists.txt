cmake_minimum_required(VERSION 3.26)

project(NetCode)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

include_directories(lib/asio net_common)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_subdirectory(net_client)
add_executable(NetCode ${SOURCES})

if(MINGW)
  target_link_libraries(NetCode ws2_32)
endif()