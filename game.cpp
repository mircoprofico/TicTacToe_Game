#include <iostream>
#include "game.h"

Game::Game() :
    ROW(3), COL(3),
    _currentPlayer(Player::PLAYER_1),
    _state(GameState::IN_PROGRESS),
    _grid(ROW, std::vector<Player>(COL, Game::Player::NONE)), // On initialise la matrice _grid(3, vector<Player>(3, '*') )
    nbOfPlay(0) {}

Game::Game(size_t row, size_t col) : ROW(row), COL(col) {}


Game::GameState Game::getStatus() const { return _state; }
Game::Player Game::getPlayer() const {}

size_t Game::getRow() const { return ROW; }
size_t Game::getCol() const { return COL; }

void Game::play(size_t row, size_t col) {}

void Game::displayPositionOnTheGrid(uint pos1, uint pos2) {
    //grid[pos1][pos2];
}
void Game::makeMove(char wichPlayer) {
    const char ROND = 'O';
    const char CROIX = 'X';
    uint pos1, pos2;
    if (wichPlayer == ROND) {
    std::cout << "Joueur " << ROND << ", choisir position : ";
    std::cin >> pos1;
    std::cin >> pos2;
    displayPositionOnTheGrid(pos1, pos2);
    } else {
        std::cout << "Joueur " << CROIX << ", a vous de jouer";
        displayPositionOnTheGrid(1, 3);
    }
    }

void Game::changePlayer() {}

bool Game::isGameOver() {}

bool Game::checkWinRow() const {
    return true;
}
bool Game::checkWinCol() const {}
bool Game::checkWinVerticalUp() const {}
bool Game::checkWinVerticalDown() const {}




