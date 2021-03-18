//
// Created by Balint on 2020. 05. 11..
//
#include <string>
#include "bot2.hpp"

int valuenekem[5] = {0, 3, 50, 200, 6000};
int valueneki[5] = {0, 2, 49, 199, 5999};

Bot2::Bot2(Map &map, std::string name, field mark) : User(name, mark) {
//std::cout << "Bot2 konstruktor" << std::endl;
    msize = map.getsize();
    valuetable = new int *[msize];
    for (int i = 0; i < msize; ++i)
        valuetable[i] = new int[msize];

    for (int i = 0; i < msize; ++i)
        for (int j = 0; j < msize; ++j)
            valuetable[i][j] = 0;
}

bool Bot2::step(Map &map, field mark) {
    int m = map.getsize();

    int forwin;
    field **table = map.gettable();

    if (map.getsize() == 3)
        forwin = 3;
    if (map.getsize() == 5 || map.getsize() == 9)
        forwin = 5;

    //oszlopokban
    for (int y = 0; y < m; ++y) {
        for (int x = 0; x < (m - (forwin - 1)); ++x) {
            oszlopvalue(map, x, y, forwin, mark);
            oszlop3(map, x, y, forwin, mark);
        }
    }
    //sorokban
    for (int x = 0; x < m; ++x) {
        for (int y = 0; y < (m - (forwin - 1)); ++y) {
            sorvalue(map, x, y, forwin, mark);
            sor3(map, x, y, forwin, mark);
        }
    }
    //atlo 11->55
    for (int x = 0; x < (m - (forwin - 1)); x++)
        for (int y = 0; y < (m - (forwin - 1)); ++y) {
            foatlovalue(map, x, y, forwin, mark);
        }
    //atlo 51->15
    for (int x = forwin - 1; x < m; ++x) {
        for (int y = 0; y < (m - (forwin - 1)); ++y) {
            mellekatlovalue(map, x, y, forwin, mark);
        }
    }

    if (map.getsize() > forwin) {

    }

    int maxX = 0;
    int maxY = 0;
    int maxvalue = table[0][0];

    for (int i = 0; i < map.getsize(); ++i) {
        for (int j = 0; j < map.getsize(); ++j) {
            if (!map.emptycheck(table, i + 1, j + 1))
                valuetable[i][j] = 0;

            std::cout << valuetable[i][j] << " ";
            if (maxvalue < valuetable[i][j]) {
                maxvalue = valuetable[i][j];
                maxX = i;
                maxY = j;
            }
        }
        std::cout << std::endl;
    }
    map(maxX + 1, maxY + 1, mark);
    return false;
}

void Bot2::oszlopvalue(Map &map, int x, int y, int forwin, field mark) {
    int nekem = 0, neki = 0, value = 0;
    field enemymark;
    if (mark == X)
        enemymark = O;
    else enemymark = X;
    field **table = map.gettable();
    for (int i = x; i < x + forwin; ++i) {
        if (table[i][y] == mark)
            nekem++;
        if (table[i][y] == enemymark)
            neki++;
    }

    if (nekem == 0)
        value = valueneki[neki];
    if (neki == 0)
        value = valuenekem[nekem];

    for (int i = x; i < x + forwin; i++)
        if (map.emptycheck(table, i + 1, y + 1))
            valuetable[i][y] += value;
}

void Bot2::oszlop3(Map &map, int x, int y, int forwin, field mark) {
    field **table = map.gettable();
    field enemymark;
    if (mark == X)
        enemymark = O;
    else enemymark = X;

    if (table[x + 1][y] == enemymark && table[x + 2][y] == enemymark && table[x + 3][y] == enemymark &&
        table[x + 4][y] == mark)
        valuetable[x][y] -= 300;
    if (table[x + 1][y] == mark && table[x + 2][y] == enemymark && table[x + 3][y] == enemymark &&
        table[x + 4][y] == enemymark)
        valuetable[x][y] -= 300;
}

void Bot2::sorvalue(Map &map, int x, int y, int forwin, field mark) {
    int nekem = 0, neki = 0, value = 0;
    field enemymark;
    if (mark == X)
        enemymark = O;
    else enemymark = X;
    field **table = map.gettable();
    for (int i = y; i < y + forwin; ++i) {
        if (table[x][i] == mark)
            nekem++;
        if (table[x][i] == enemymark)
            neki++;
    }

    if (nekem == 0)
        value = valueneki[neki];
    if (neki == 0)
        value = valuenekem[nekem];

    for (int i = y; i < y + forwin; i++)
        if (map.emptycheck(table, x + 1, i + 1))
            valuetable[x][i] += value;
}

void Bot2::sor3(Map &map, int x, int y, int forwin, field mark) {
    field **table = map.gettable();
    field enemymark;
    if (mark == X)
        enemymark = O;
    else enemymark = X;

    if (table[x][y + 1] == mark && table[x][y + 2] == mark && table[x][y + 3] == mark && table[x][y + 4] == enemymark)
        valuetable[x][y] -= 150;
}

void Bot2::foatlovalue(Map &map, int x, int y, int forwin, field mark) {
    int nekem = 0, neki = 0, value = 0;
    field enemymark;
    if (mark == X)
        enemymark = O;
    else enemymark = X;
    field **table = map.gettable();
    for (int i = 0; i < forwin; ++i) {
        if (table[x + i][y + i] == mark)
            nekem++;
        if (table[x + i][y + i] == enemymark)
            neki++;
    }

    if (nekem == 0)
        value = valueneki[neki];
    if (neki == 0)
        value = valuenekem[nekem];

    for (int i = 0; i < forwin; i++)
        if (map.emptycheck(table, x + i + 1, y + i + 1))
            valuetable[x + i][y + i] += value;
}

void Bot2::mellekatlovalue(Map &map, int x, int y, int forwin, field mark) {
    int nekem = 0, neki = 0, value = 0;
    field enemymark;
    if (mark == X)
        enemymark = O;
    else enemymark = X;
    field **table = map.gettable();
    for (int i = 0; i < forwin; ++i) {
        if (table[x - i][y + i] == mark)
            nekem++;
        if (table[x - i][y + i] == enemymark)
            neki++;
    }

    if (nekem == 0)
        value = valueneki[neki];
    if (neki == 0)
        value = valuenekem[nekem];

    for (int i = 0; i < forwin; i++)
        if (map.emptycheck(table, x - i + 1, y + i + 1))
            valuetable[x - i][y + i] += value;
}

Bot2::~Bot2() {
    // std::cout << "bot2 destruktor hivodik" << std::endl;
    for (int i = 0; i < msize; ++i) {
        delete[] valuetable[i];
    }
    delete[] valuetable;
}

