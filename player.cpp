//
// Created by Balint on 2020. 05. 11..
//

#include "player.hpp"
#include <math.h>


bool Player::step(Map &map, field mark) {
    int x, y = 0;

    std::cout << "Add meg hova szeretnel rakni: " << std::endl << "Sor: ";
    std::cin >> x;
    if (!isnan(x)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }

    std::cout << "Oszlop: ";
    std::cin >> y;
    if (!isnan(y)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }

    if (x == 0 && y == 0) {
        map.save();
        return true;
    }
    if (map.valid(x, y, map.getsize()) && map.emptycheck(map.gettable(), x, y))
        map(x, y, mark);
    else {
        std::cout << "Ez a pont nincs a palyan vagy mar foglalt!" << std::endl;
        Player::step(map, mark);
    }
    return false;
}

