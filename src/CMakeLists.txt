project(sysrepopg)

cmake_minimum_required(VERSION 3.5)

add_executable(sysrepopg main.cpp)

target_link_libraries(sysrepopg PRIVATE sysrepo)