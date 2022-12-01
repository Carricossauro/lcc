cmake_minimum_required(VERSION 3.15)
project(Projeto_LA C)

set(CMAKE_C_STANDARD 99)

add_executable(Projeto_LA main.c dados.c dados.h logica.c logica.h interface.c interface.h listas.c listas.h minimax.c minimax.h)
target_link_libraries(Projeto_LA m)