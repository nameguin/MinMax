cmake_minimum_required(VERSION 3.29)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(untitled main.cpp
        src/Connect4.cpp
        src/SticksGame.cpp
        src/TicTacToe.cpp
        include/Game.h
        include/SticksGame.h
)
