cmake_minimum_required(VERSION 4.0)
project(2025_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(2025_2 main.cpp
        Biblioteca/Nodo.h
        Biblioteca/Jugador.h
        Biblioteca/Lista.h
        Biblioteca/Funciones.cpp
        Biblioteca/Funciones.h)
