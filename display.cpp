#include <iostream>
#include "display.h"

Display::Display(const Game& game) : game(game){
}

void Display::run() {
    while (game.isRunning()) {
        std::cout << std::endl;
        displayGrid(ROW, COL);
        std::cout << std::endl;
        game.play();
    }
    std::cout << std::endl;
    displayGrid(ROW, COL);
    std::cout << std::endl << "Game Over, ";
    switch (game.getStatus()) {
        case Game::GameState::PLAYER_1_WIN :
            std::cout << "Player X Win !";
        case Game::GameState::PLAYER_2_WIN :
            std::cout << "Player O Win !";
        case Game::GameState::DRAW :
            std::cout << "Draw";
    }
}

void Display::displayGrid(size_t row, size_t col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j){
            Game::Player cell = game.getCell(i, j);  // Récupère la valeur de la cellule (i, j)
            if (cell == Game::Player::PLAYER_1) {
                std::cout << "O" << " ";
            } else if (cell == Game::Player::PLAYER_2){
                std::cout << "X" << " ";
            } else {
                std::cout << "*" << " ";
            }
        }
        std::cout << std::endl;
    }
}
