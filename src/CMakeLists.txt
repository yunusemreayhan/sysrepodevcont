project(sysrepopg)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

cmake_minimum_required(VERSION 3.5)

add_executable(sysrepopg main.cpp)

target_link_libraries(sysrepopg PRIVATE sysrepo)