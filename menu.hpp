//
// Created by Balint on 2020. 04. 27..
//
#include "game.hpp"
#include <fstream>
#include <iostream>
#include "gamemode.hpp"

#ifndef NHF_MENU_HPP
#define NHF_MENU_HPP

#include "state.hpp"

class Menu {
    int msize = 3;
    gamemode mode = bot_1;
    field **loadtable;
    int playedgame = 0;
public:
    Menu();

    gamemode mode_set();

    int mapsize_set();

    void fault(int ina);

    void tableload();

    void load();

    ~Menu();
};


#endif //NHF_MENU_HPP
