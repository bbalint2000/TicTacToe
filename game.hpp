//
// Created by Balint on 2020. 04. 27..
//

#include "map.hpp"
#include "gamemode.hpp"
#include "user.hpp"
#include "player.hpp"
#include "bot1.hpp"
#include "bot2.hpp"
#include <math.h>

#ifndef NHF_GAME_HPP
#define NHF_GAME_HPP

class Game {
    field onTurn = X;
    User *players[2];
    bool win = false;
    bool tie = false;
public:
    Game(int msize, gamemode mode, field **&loadtable);

    field nextturn(field onTurn);

    ~Game();

    field first();

    bool wincheck(Map &map);

    bool tiecheck(Map &map);

    bool sorwin(field mark, int x, int y, field **table, int forwin);

    bool oszlopwin(field mark, int x, int y, field **table, int forwin);

    bool foatlowin(field mark, int x, int y, field **table, int forwin);

    bool mellekatlowin(field mark, int x, int y, field **table, int forwin);


};

#endif //NHF_GAME_HPP
