//
// Created by Balint on 2020. 04. 27..
//

#ifndef NHF_MAP_HPP
#define NHF_MAP_HPP

#include "field.hpp"
#include <iostream>
#include <fstream>
#include "gamemode.hpp"

class Map {
    field **table;
    int msize;
    gamemode mode;
public:
    Map(int m, gamemode mode, field **&loadtable);

    void print_out();

    field **gettable() const;

    int getsize() const;

    void operator()(int x, int y, field mark);

    bool valid(int x, int y, int msize);

    bool emptycheck(field **table, int x, int y);

    void save();

    ~Map();
};


#endif //NHF_MAP_HPP
