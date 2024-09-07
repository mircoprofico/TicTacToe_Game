#include <iostream>
#include "game.h"

Game::Game() :
    ROW(3), COL(3),
    _currentPlayer(Game::Player::PLAYER_1),
    _state(GameState::IN_PROGRESS),
    _nbOfPlay(0) {
    _grid = std::vector<std::vector<Player>>(ROW, std::vector<Player>(COL, Game::Player::NONE));

}

Game::Game(size_t row, size_t col) :
    ROW(row), COL(col),
    _currentPlayer(Game::Player::PLAYER_1),
    _state(GameState::IN_PROGRESS),
    _nbOfPlay(0) {
    _grid = std::vector<std::vector<Player>>(ROW, std::vector<Player>(COL, Game::Player::NONE));
}


Game::GameState Game::getStatus() const { return _state; }
Game::Player Game::getPlayer() const { return _currentPlayer;}
size_t Game::getRow() const { return ROW; }
size_t Game::getCol() const { return COL; }

Game::Player Game::getCell(size_t row, size_t col) const { return _grid[row][col]; }

void Game::play() { makeMove(getPlayer()); }

void Game::displayPositionOnTheGrid(uint pos1, uint pos2) { _grid[pos1][pos2] = _currentPlayer; }

void Game::makeMove(Game::Player whichPlayer) {
    uint pos1, pos2;
    std::cout << (whichPlayer == Player::PLAYER_1 ? "Joueur O" : "Joueur X") << ", a vous de jouer" << std::endl;
    std::cout << "Position 1 :  ";
    std::cin >> pos1;
    std::cout << std::endl << "Position 2 :  ";
    std::cin >> pos2;
    displayPositionOnTheGrid(pos1, pos2);
    changePlayer(); // Change le joueur après le coup
    }

Game::Player Game::changePlayer() {
    return _currentPlayer = (_currentPlayer == Game::Player::PLAYER_1) ? Game::Player::PLAYER_2 :
                                                                         Game::Player::PLAYER_1;
    }


bool Game::isGameOver() {}

bool Game::checkWinRow() const { return true; }
bool Game::checkWinCol() const {}
bool Game::checkWinVerticalUp() const {}
bool Game::checkWinVerticalDown() const {}




