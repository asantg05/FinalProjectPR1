cmake_minimum_required(VERSION 3.8)
project(FP_Base C)

set(CMAKE_C_STANDARD 90)

add_executable(FP_Base main.c docente.c docente.h creacionListas.c creacionListas.h territorios.c territorios.h juego.c juego.h)