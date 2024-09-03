#include <iostream>
#include "display.h"


Display::Display(const Game& game) : game(game){
    appIsRunning = true;
}

void Display::run() {
//TODO  mettre la boucle while appIsRunning
        displayGrid(ROW, COL);
}

void Display::displayGrid(size_t row, size_t col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            std::cout << '*' << ' ';
        }
        std::cout << std::endl;
    }
}
