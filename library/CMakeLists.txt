cmake_minimum_required(VERSION 4.1)
project(library)

set(CMAKE_CXX_STANDARD 23)

add_executable(library main.cpp
        Library.cpp
        Library.h
        Bookshelves.cpp
        Bookshelves.h
        Person.cpp
        Person.h
        Employee.cpp
        Employee.h)
