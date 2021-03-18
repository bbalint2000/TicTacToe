//
// Created by Balint on 2020. 04. 27..
//

#include "game.hpp"
#include "menu.hpp"


Game::Game(int msize, gamemode mode, field **&loadtable) {
    Map map(msize, mode, loadtable);
    std::string name;
    std::cout << "Elso jatekos neve?" << std::endl;
    std::cin >> name;

    players[0] = new Player(name);

    if (mode == two_player) {
        std::string name2;
        std::cout << "Masodik jatekos neve?" << std::endl;
        std::cin >> name2;
        players[1] = new Player(name2);
        onTurn = Game::first();
        std::cout << "A jatekmod: ketjatekos" << std::endl;
    }
    if (mode == bot_1) {
        std::cout << "A jatekmod: konnyu bot" << std::endl;
        players[1] = new Bot1("Bot1", onTurn);
        onTurn = O;

    }
    if (mode == bot_2) {
        std::cout << "A jatekmod: nehez bot" << std::endl;
        players[1] = new Bot2(map, "Bot2", onTurn);
        onTurn = X;
    }

    std::cout << "Kezdodik a jatek!" << std::endl;
    std::cout << "Ha a sor es oszlop helyere 0-at irsz, akkor tudod elmenteni a jatekod!" << std::endl;
    map.print_out();

    bool out = false;

    while (!win && !tie && !out) {
        if (onTurn == X)
            out = players[0]->step(map, onTurn);
        else out = players[1]->step(map, onTurn);
        map.print_out();
        win = wincheck(map);
        if (!win)
            tie = tiecheck(map);
        onTurn = nextturn(onTurn);
    }
}

Game::~Game() {
    std::cout << "game destruktor" << std::endl;
    delete players[0];
    delete players[1];
}

field Game::first() {
    int in;
    std::cout << players[0]->getname() << " az X" << std::endl << players[1]->getname() << " a O" << std::endl <<
              "Ki kezdjen?" << std::endl << players[0]->getname() << " (1)" << std::endl << players[1]->getname()
              << " (2)" << std::endl;
    std::cin >> in;
    if (!isnan(in)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');

    }
    if (in == 1)
        return X;
    else if (in == 2)
        return O;
    else return Game::first();
}

field Game::nextturn(field onturn) {
    return (onturn == X ? O : X);
}

bool Game::wincheck(Map &map) {
    field **table = map.gettable();
    int forwin;
    field mark;

    if (map.getsize() == 3)
        forwin = 3;
    if (map.getsize() == 5 || map.getsize() == 9)
        forwin = 5;

    //sor
    for (int x = 0; x < map.getsize(); ++x) {
        for (int y = 0; y < (map.getsize() - (forwin - 1)); ++y) {
            if (table[x][y] == X)
                mark = X;
            else mark = O;
            win = sorwin(mark, x, y, map.gettable(), forwin);
            if (win) return true;
        }
    }
    //oszlop
    for (int y = 0; y < map.getsize(); ++y) {
        for (int x = 0; x < (map.getsize() - (forwin - 1)); ++x) {
            if (table[x][y] == X)
                mark = X;
            else mark = O;
            win = oszlopwin(mark, x, y, map.gettable(), forwin);
            if (win) return true;
        }
    }
    //foatlo
    for (int x = 0; x < (map.getsize() - (forwin - 1)); x++) {
        for (int y = 0; y < (map.getsize() - (forwin - 1)); ++y) {
            if (table[x][y] == X)
                mark = X;
            else mark = O;
            win = foatlowin(mark, x, y, map.gettable(), forwin);
            if (win) return true;
        }
    }
    //mellekatlo
    for (int x = forwin - 1; x < map.getsize(); ++x) {
        for (int y = 0; y < (map.getsize() - (forwin - 1)); ++y) {
            if (table[x][y] == X)
                mark = X;
            else mark = O;
            win = mellekatlowin(mark, x, y, map.gettable(), forwin);
            if (win) return true;
        }
    }
    return false;
}


bool Game::sorwin(field mark, int x, int y, field **table, int forwin) {
    int cnt = 0;
    for (int i = y; i < y + forwin; i++) {
        if (table[x][i] == mark)
            ++cnt;
        if (table[x][i] != mark)
            cnt = 0;
        if (cnt == forwin) {
            std::cout << "Nyert ";
            if (mark == X)
                std::cout << "X" << std::endl;
            else
                std::cout << "O" << std::endl;
            return true;
        }
    }
    return false;
}

bool Game::oszlopwin(field mark, int x, int y, field **table, int forwin) {
    int cnt = 0;
    for (int i = x; i < x + forwin; i++) {
        if (table[i][y] == mark)
            ++cnt;
        if (table[i][y] != mark)
            cnt = 0;
        if (cnt == forwin) {
            std::cout << "Nyert ";
            if (mark == X)
                std::cout << "X" << std::endl;
            else
                std::cout << "O" << std::endl;
            return true;
        }
    }
    return false;
}

bool Game::foatlowin(field mark, int x, int y, field **table, int forwin) {
    int cnt = 0;
    for (int i = 0; i < forwin; i++) {
        if (table[x + i][y + i] == mark)
            ++cnt;
        if (table[x + i][y + i] != mark)
            cnt = 0;
        if (cnt == forwin) {
            std::cout << "Nyert ";
            if (mark == X)
                std::cout << "X" << std::endl;
            else
                std::cout << "O" << std::endl;
            return true;
        }
    }
    return false;
}

bool Game::mellekatlowin(field mark, int x, int y, field **table, int forwin) {
    int cnt = 0;
    for (int i = 0; i < forwin; i++) {
        if (table[x - i][y + i] == mark)
            ++cnt;
        if (table[x - i][y + i] != mark)
            cnt = 0;
        if (cnt == forwin) {
            std::cout << "Nyert ";
            if (mark == X)
                std::cout << "X" << std::endl;
            else
                std::cout << "O" << std::endl;
            return true;
        }
    }
    return false;
}

bool Game::tiecheck(Map &map) {
    field **table = map.gettable();
    int cnt = 0;
    for (int i = 0; i < map.getsize(); ++i)
        for (int j = 0; j < map.getsize(); ++j)
            if (table[i][j] != empty)
                cnt++;

    if (cnt == (map.getsize() * map.getsize())) {
        std::cout << "Dontetlen" << std::endl;
        return true;
    }
    return false;
}
