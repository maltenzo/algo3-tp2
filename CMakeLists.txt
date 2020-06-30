cmake_minimum_required(VERSION 3.16)
project(tp2_github)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Tests)

add_executable(tp2_github
        Tests/tests.cpp
        Tests/tests.h
        2opt.cpp
        funciones.h

        heurAGM.cpp
        Insercion.cpp
        main.cpp)
