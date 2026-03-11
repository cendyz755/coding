cmake_minimum_required(VERSION 4.1)
project(library)

set(CMAKE_CXX_STANDARD 23)

add_executable(library src/main.cpp
        src/Library.cpp
        include/library/Library.h
        src/Books.cpp
        include/library/Books.h
        src/Registered_people.cpp
        include/library/Registered_people.h
        src/Employees.cpp
        include/library/Employees.h)
