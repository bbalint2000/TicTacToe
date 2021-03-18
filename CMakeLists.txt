cmake_minimum_required(VERSION 3.15)
project(NHF)

set(CMAKE_CXX_STANDARD 14)

add_executable(NHF main.cpp menu.cpp menu.hpp game.cpp game.hpp map.cpp map.hpp gamemode.hpp field.hpp user.cpp user.hpp player.hpp bot1.hpp bot2.hpp player.cpp bot1.cpp bot2.cpp state.hpp)