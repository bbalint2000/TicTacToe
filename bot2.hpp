//
// Created by Balint on 2020. 05. 08..
//

#ifndef NHF_BOT2_HPP
#define NHF_BOT2_HPP

#include "user.hpp"
#include "map.hpp"

class Bot2 : public User {
    int **valuetable;
    int msize;
public:
    Bot2(Map &map, std::string name, field mark);

    bool step(Map &map, field mark);

    void oszlopvalue(Map &map, int x, int y, int forwin, field mark);

    void sorvalue(Map &map, int x, int y, int forwin, field mark);

    void foatlovalue(Map &map, int x, int y, int forwin, field mark);

    void mellekatlovalue(Map &map, int x, int y, int forwin, field mark);

    ~Bot2();

    void oszlop3(Map &map, int x, int y, int forwin, field mark);

    void sor3(Map &map, int x, int y, int forwin, field mark);
};

#endif //NHF_BOT2_HPP
