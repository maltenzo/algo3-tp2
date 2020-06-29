cmake_minimum_required(VERSION 3.16)
project(tp2)

set(CMAKE_CXX_STANDARD 14)

add_executable(tp2
        main.cpp
        funciones.h
        heurAGM.cpp
        Insercion.cpp
        Tests/tests.h Tests/tests.cpp
        2opt.cpp)