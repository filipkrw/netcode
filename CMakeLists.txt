cmake_minimum_required(VERSION 3.26)

project(NetCode)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

if (WIN32)
  set(CMAKE_C_COMPILER "C:/Program Files (x86)/Microsoft Visual Studio/2022/BuildTools/VC/Tools/MSVC/14.39.33519/bin/Hostx64/x64/cl.exe")
  set(CMAKE_CXX_COMPILER  "C:/Program Files (x86)/Microsoft Visual Studio/2022/BuildTools/VC/Tools/MSVC/14.39.33519/bin/Hostx64/x64/cl.exe")
endif()

include_directories(lib/asio net_common)
file(GLOB_RECURSE SOURCES src/*.cpp)

# add_subdirectory(net_client)
# add_subdirectory(net_server)

add_subdirectory(mmo/client)
add_subdirectory(mmo/server)
add_executable(NetCode ${SOURCES})

if(MINGW)
  target_link_libraries(NetCode ws2_32 wsock32)
endif()