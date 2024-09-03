cmake_minimum_required(VERSION 3.26)
project(tictactoe)

set(CMAKE_CXX_STANDARD 20)

add_executable(tictactoe main.cpp
        game.h
        game.cpp
        display.h
        display.cpp
        display.cpp)
