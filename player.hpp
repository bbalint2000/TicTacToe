//
// Created by Balint on 2020. 05. 08..
//

#ifndef NHF_PLAYER_HPP
#define NHF_PLAYER_HPP

#include "user.hpp"

class Player : public User {

public:
    Player(std::string name) : User(name, mark) {}

    bool step(Map &map, field mark);

    ~Player() {};
};

#endif //NHF_PLAYER_HPP
