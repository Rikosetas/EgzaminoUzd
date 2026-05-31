cmake_minimum_required(VERSION 3.10)

project(EgzaminoUzd)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(EgzaminoUzd EgzaminoUzd.cpp)

configure_file(${CMAKE_SOURCE_DIR}/tekstas.txt ${CMAKE_BINARY_DIR}/tekstas.txt COPYONLY)
