cmake_minimum_required(VERSION 3.29)
project(c_future C)

set(CMAKE_C_STANDARD 11)

add_executable(c_future main.c
        future.h
        future.c)
