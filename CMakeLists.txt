cmake_minimum_required(VERSION 3.12)
project(TCC C)

set(CMAKE_C_STANDARD 11)

add_executable(TCC src/main.c src/util.c src/util.h)