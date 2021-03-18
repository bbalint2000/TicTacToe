//
// Created by Balint on 2020. 05. 05..
//

#include "user.hpp"


User::User(std::string name, field mark) {
    //  std::cout << "User konstruktor" << std::endl;
    this->name = name;
    this->mark = mark;
}

std::string User::getname() const {
    return name;
}

User::~User() {
//std::cout << "user destruktor" << std::endl;
}


