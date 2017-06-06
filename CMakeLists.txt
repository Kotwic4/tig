cmake_minimum_required(VERSION 3.6)
project(TIG)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES tig.c)
add_executable(TIG ${SOURCE_FILES})