//
// Created by Balint on 2020. 05. 08..
//

#ifndef NHF_BOT1_HPP
#define NHF_BOT1_HPP

#include "user.hpp"

class Bot1 : public User {
public:
    Bot1(std::string name, field mark) : User(name, mark) {};

    bool step(Map &map, field onturn);

    ~Bot1() {};

};

#endif //NHF_BOT1_HPP
