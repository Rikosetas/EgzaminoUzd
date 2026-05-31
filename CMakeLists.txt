cmake_minimum_required(VERSION 3.10)

project(EgzaminoUzd)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(EgzaminoUzd EgzaminoUzd.cpp)

configure_file(${CMAKE_SOURCE_DIR}/tekstas.txt ${CMAKE_BINARY_DIR}/tekstas.txt COPYONLY)

add_custom_command(TARGET EgzaminoUzd POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/tekstas.txt
    $<TARGET_FILE_DIR:EgzaminoUzd>/tekstas.txt)
