cmake_minimum_required(VERSION 3.23)
project(ex1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(tests)

add_executable(ex1
        tool/main.c
        tool/AsciiArtTool.c
        tool/AsciiArtTool.h
        RLEList.c
        RLEList.h)
