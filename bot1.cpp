//
// Created by Balint on 2020. 05. 11..
//

#include "bot1.hpp"
#include <time.h>

bool Bot1::step(Map &map, field onturn) {
    srand(time(NULL));
    int randx;
    int randy;

    do {
        randx = rand() % map.getsize();
        randy = rand() % map.getsize();
        randx++;
        randy++;
    } while (!map.emptycheck(map.gettable(), randx, randy));

    map(randx, randy, onturn);
    return false;
}