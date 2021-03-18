//
// Created by Balint on 2020. 04. 27..
//

#include "map.hpp"

//lefoglalja a table-nek a helyet, majd feltölti
Map::Map(int m, gamemode mode, field **&loadtable) {
    this->mode = mode;
    std::cout << "A palya merete: " << m << "x" << m << std::endl;
    msize = m;
    table = new field *[m];
    for (int i = 0; i < m; ++i)
        table[i] = new field[m];


    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j) {
            if (loadtable[i][j] == empty)
                table[i][j] = empty;
            if (loadtable[i][j] == X)
                table[i][j] = X;
            if (loadtable[i][j] == O)
                table[i][j] = O;
        }


    table[3][3] = X;
    table[4][3] = X;
    table[5][3] = X;

}

//kirajzolja a pályát.
void Map::print_out() {
    field **t = gettable();

    std::cout << "_";
    std::cout << "|";
    for (int i = 0; i < msize; i++) {
        std::cout << "__" << i + 1 << "__|";
    }
    std::cout << std::endl;

    std::cout << " ";
    std::cout << "|";
    for (int i = 0; i < msize; i++) {
        std::cout << "     |";
    }
    std::cout << std::endl;


    for (int i = 0; i < msize; i++) {
        std::cout << i + 1;
        std::cout << "|";
        for (int j = 0; j < msize; j++) {
            if (t[i][j] == X)
                std::cout << "  " << "X" << "  |";
            else if (t[i][j] == O)
                std::cout << "  " << "O" << "  |";
            else if (t[i][j] == empty)
                std::cout << "  " << " " << "  |";
            // else std::cout <<"  " << "G" << "  |"; hibakezelés
        }
        std::cout << std::endl;

        std::cout << "_";
        std::cout << "|";
        for (int k = 0; k < msize; k++) {
            std::cout << "_____|";
        }
        std::cout << std::endl;

        std::cout << " ";
        std::cout << "|";
        for (int k = 0; k < msize; k++) {
            std::cout << "     |";
        }
        std::cout << "     " << std::endl;
    }
}


field **Map::gettable() const {
    return table;
}

int Map::getsize() const {
    return msize;
}

//elhelyezi a table-ben a játékos jelét
void Map::operator()(int x, int y, field mark) {
    table[x - 1][y - 1] = mark;
}

//megvizsgálja, hogy a megadott koordináták a pálán vannak e
bool Map::valid(int x, int y, int msize) {
    return (0 < x && x <= msize &&
            0 < y && y <= msize);
}

Map::~Map() {
    //  std::cout << "map destruktor hivodik" << std::endl;
    for (int i = 0; i < msize; ++i) {
        delete[] table[i];
    }
    delete[] table;

}

//megvizsgálja, hogy a megadott koordináták helyén van e már jel
bool Map::emptycheck(field **table, int x, int y) {
    if (table[x - 1][y - 1] == empty)
        return true;
    else return false;
}

//elmentia jatek allasat egy külső fájlba
void Map::save() {
    std::ofstream file;
    std::string fname;
    std::cout << "Add meg a fajl nevet" << std::endl;
    std::cin >> fname;
    fname += ".txt";
    file.open(fname);
    if (file.is_open()) {
        file << Map::getsize() << std::endl;

        if (mode == two_player)
            file << "1" << std::endl;
        if (mode == bot_1)
            file << "2" << std::endl;
        if (mode == bot_2)
            file << "3" << std::endl;

        for (int i = 0; i < msize; ++i) {
            for (int j = 0; j < msize; ++j) {
                if (table[i][j] == X)
                    file << "X ";
                if (table[i][j] == O)
                    file << "O ";
                if (table[i][j] == empty)
                    file << "_ ";
            }
            file << std::endl;
        }
        file.close();
    } else std::cout << "Nem sikerult a fileba iras" << std::endl;

}
