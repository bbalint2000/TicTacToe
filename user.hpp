//
// Created by Balint on 2020. 05. 05..
//
#include <iostream>
#include "field.hpp"
#include "map.hpp"

#ifndef NHF_USER_HPP
#define NHF_USER_HPP

class User {
    std::string name;
public:
    User(std::string name, field mark);

    virtual bool step(Map &map, field onturn) = 0;

    std::string getname() const;

    virtual ~User();

protected:
    field mark;

};

#endif //NHF_USER_HPP
