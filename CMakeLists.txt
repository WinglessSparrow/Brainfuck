cmake_minimum_required(VERSION 4.0)
project(Brainfuck C)

set(CMAKE_C_STANDARD 23)

add_executable(
        Brainfuck
        main.c
        src/vector_2.c
        include/vector_2.h
)
