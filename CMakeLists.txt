cmake_minimum_required(VERSION 3.12)
project(TCC C)

set(CMAKE_C_STANDARD 11)

add_library(Chapter1 src/util.c src/util.h src/slp.c src/slp.h)

add_subdirectory(src/exercises)