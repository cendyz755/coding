cmake_minimum_required(VERSION 4.1)
project(bank)

set(CMAKE_CXX_STANDARD 23)

add_executable(Bank.cpp
        Bank.h
        main.cpp
        Bank.cpp)
