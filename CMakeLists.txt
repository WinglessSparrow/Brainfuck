cmake_minimum_required(VERSION 4.0)
project(Brainfuck C)

set(CMAKE_C_STANDARD 23)

add_executable(
        Brainfuck
        main.c
        src/vector.c
        src/commandsSpace.c
        include/commandsSpace.h
        include/pointerSpace.h
        include/vector.h
        src/pointerSpace.c
        include/fileReader.h
        src/runner.c
)
