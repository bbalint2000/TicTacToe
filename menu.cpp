//
// Created by Balint on 2020. 04. 27..
//

#include "menu.hpp"
#include "game.hpp"

//menu konstruktor, tartalmazza a játék menüjét
Menu::Menu() {
    State state = menu;
    int in;
    if (playedgame == 0) {
        loadtable = new field *[9];
        for (int i = 0; i < 9; ++i)
            loadtable[i] = new field[9];

        playedgame++;
    }


    while (state != end) {
        std::cout << "Jatek (1)" << std::endl;
        std::cout << "Regi jatek betoltese (2)" << std::endl;
        std::cout << "Jatekmod beallitasa (3)" << std::endl;
        std::cout << "Palya meret beallitasa (4)" << std::endl;
        std::cout << "Kilepes (5)" << std::endl;
        std::cin >> in;

        if (!isnan(in)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }


        switch (in) {
            case 1:
                state = play;
                tableload();
                Game(msize, mode, loadtable);
                break;
            case 2:
                state = loadgame;
                load();
                Game(msize, mode, loadtable);
                break;
            case 3:
                state = setmode;
                mode = mode_set();
                break;
            case 4:
                state = setmap;
                msize = mapsize_set();
                break;
            case 5:
                state = end;
                break;
            default:
                state = menu;
                break;
        }
    }
}

//jatekmod beallitasa
gamemode Menu::mode_set() {
    int in = 0;
    std::cout << "Hogy szeretnel jatszani?" << std::endl;
    std::cout << "Jatekos jatekos ellen (1)" << std::endl;
    std::cout << "Konnyu bot ellen (2)" << std::endl;
    std::cout << "Nehez bot ellen (3)" << std::endl;
    std::cin >> in;
    fault(in);

    switch (in) {
        case 1:
            return two_player;
            break;
        case 2:
            return bot_1;
            break;
        case 3:
            return bot_2;
            break;
        default:
            std::cout << "Ilyen lehetoseg nincs" << std::endl;
            break;
    }
    return bot_1;
}

//palya meret beallitasa
int Menu::mapsize_set() {
    int in = 0;
    std::cout << "Mekkora legyen a palya?" << std::endl << "3x3 (1)" << std::endl << "5x5 (2)" << std::endl << "9x9 (3)"
              << std::endl;
    std::cin >> in;
    fault(in);


    if (in == 1) return 3;
    else if (in == 2) return 5;
    else if (in == 3) return 9;
    else {
        std::cout << "Rossz gombot nyomtal" << std::endl;
        Menu::mapsize_set();
    }
    return 3;
}


//feltölti üresre a loadtable-t
void Menu::tableload() {

    for (int i = 0; i < msize; ++i)
        for (int j = 0; j < msize; ++j)
            loadtable[i][j] = empty;
}

//hiba kezelés
void Menu::fault(int in) {
    if (!isnan(in)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');

    }
}

//külső fájlból beolvasás
void Menu::load() {
    std::ifstream file;
    std::string fname, ssize, smode, tab;
    int n;
    std::cout << "Add meg a fajl nevet" << std::endl;
    std::cin >> fname;
    fname += ".txt";
    file.open(fname);

    if (file.is_open()) {
        //palya meret beolvasas
        std::getline(file, ssize);
        msize = std::atoi(ssize.c_str());

        //jatekmod beolvasas
        std::getline(file, smode);
        n = std::atoi(smode.c_str());
        if (n == 1)
            mode = two_player;
        if (n == 2)
            mode = bot_1;
        if (n == 3)
            mode = bot_2;

        //palya tartalom beolv
        for (int i = 0; i < msize; ++i) {
            for (int j = 0; j < msize; ++j) {
                file >> tab;
                if (tab == "X")
                    loadtable[i][j] = X;
                if (tab == "O")
                    loadtable[i][j] = O;
                if (tab == "_")
                    loadtable[i][j] = empty;
            }
        }
        file.close();
    } else std::cout << "Nem sikerult a beolvasas" << std::endl;

}

//menu destruktor, törli a loadtable-t
Menu::~Menu() {
    //std::cout << "menu destruktor hivodik" << std::endl;
    for (int i = 0; i < msize; ++i) {
        delete[] loadtable[i];
    }
    delete[] loadtable;
}




