#include <iostream>
#include <limits>
#include "game.h"

Game::Game() :
    ROW(3), COL(3),
    _appIsRunning(true),
    _currentPlayer(Game::Player::PLAYER_1),
    _state(GameState::IN_PROGRESS),

    _nbOfPlay(0) {
    _grid = std::vector<std::vector<Player>>(ROW, std::vector<Player>(COL, Game::Player::NONE));

}

Game::Game(size_t row, size_t col) :
    ROW(row), COL(col),
    _appIsRunning(true),
    _currentPlayer(Game::Player::PLAYER_1),
    _state(GameState::IN_PROGRESS),
    _nbOfPlay(0) {
    _grid = std::vector<std::vector<Player>>(ROW, std::vector<Player>(COL, Game::Player::NONE));
}


Game::GameState Game::getStatus() const { return _state; }
Game::Player Game::getPlayer() const { return _currentPlayer;}
size_t Game::getRow() const { return ROW; }
size_t Game::getCol() const { return COL; }

bool Game::isRunning() const {
    return _appIsRunning;
}
Game::Player Game::getCell(size_t row, size_t col) const { return _grid[row][col]; }

void Game::play() {
    makeMove(getPlayer());
    ++_nbOfPlay;
    if (isGameOver()) {
        std::cout << std::endl << "Game Over, ";
        switch (getStatus()) {
            case GameState::PLAYER_1_WIN :
                std::cout << "Player X Win !";
                break;
            case GameState::PLAYER_2_WIN :
                std::cout << "Player O Win !";
                break;
            case GameState::DRAW :
                std::cout << "Draw";
                break;
        }
        _appIsRunning = false;
    }
    changePlayer();
    }

void Game::displayPositionOnTheGrid(uint pos1, uint pos2) { _grid[pos1][pos2] = _currentPlayer; }

void Game::makeMove(Game::Player whichPlayer) {
    uint pos1, pos2;
    do {
        std::cout << (whichPlayer == Player::PLAYER_1 ? "Joueur X" : "Joueur O") << ", a vous de jouer" << std::endl;
        std::cout << "Numero Ligne :  ";
        std::cin >> pos1;
        std::cout << std::endl;
        std::cout << "Numero Colonne : ";
        std::cin >> pos2;
        if (std::cin.fail() || pos1 >= static_cast<int>(ROW) || pos2 >= static_cast<int>(ROW) || pos1 < 0 || pos2 < 0) {
            std::cin.clear();  // Efface l'état d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore les entrées incorrectes
            std::cout << std::endl;
            std::cerr << "Entree invalide. Veuillez entrer un nombre valide" << std::endl;
            std::cout << std::endl;

        }
    } while (pos1 >= static_cast<int>(ROW) || pos2 >= static_cast<int>(ROW) || pos1 < 0 || pos2 < 0);
    displayPositionOnTheGrid(pos1, pos2);
}

Game::Player Game::changePlayer() {
    return _currentPlayer = (_currentPlayer == Game::Player::PLAYER_1) ? Game::Player::PLAYER_2 :
                                                                         Game::Player::PLAYER_1;
    }


bool Game::isGameOver() {
    return checkWinRow() || checkWinCol() || checkWinVerticalUp() || checkWinVerticalDown();
}

bool Game::checkWinRow()  {
    for (int row = 0; row < ROW; ++row){
        int nbrAdjCell = 0;

        for (int col = 0; col < COL; ++col) { // On itére dans chaque colonne dans la ligne actuel
            const Game::Player& valPlayer = _grid[row][col]; // Récupére la valeur actuelle
            if (valPlayer == _currentPlayer) {
                ++nbrAdjCell;
                if (nbrAdjCell == ROW){
                   _state = (_currentPlayer == Player::PLAYER_1) ? GameState::PLAYER_1_WIN : GameState::PLAYER_2_WIN;
                   return true;
                }
            } else {
                nbrAdjCell = 0;
            }
        }
    }
    return false;
}
bool Game::checkWinCol() {
    int nbrAdjCell = 0;
    int cpt = 0;
    for (int col = 0; col < COL; ++col) {
        for (int row = 0; row < ROW; ++row) {
            const Game::Player &valPlayer = _grid[row][col];
            if (valPlayer == _currentPlayer){
                nbrAdjCell++;
                if (nbrAdjCell == COL) {
                    _state = (_currentPlayer == Player::PLAYER_1) ? GameState::PLAYER_1_WIN : GameState::PLAYER_2_WIN;
                    return true;
                }
            }
            else {
                nbrAdjCell = 0;
            }
        }
    }
    return false;
}

bool Game::checkWinVerticalUp() { // '/' La diagonale montante part de (ROW-1, 0) et va jusqu'à (0, COL-1).
    int col = 0;
    int row = ROW-1;
    int nbrAdjCell = 0;

    while (row >= 0  && col < COL) {
        const Game::Player& valPlayer = _grid[row][col];
        if (valPlayer == _currentPlayer) {
            ++nbrAdjCell;
            if (nbrAdjCell == ROW){
                _state = (_currentPlayer == Player::PLAYER_1) ? GameState::PLAYER_1_WIN : GameState::PLAYER_2_WIN;
                return true;
            }
        }
        --row;
        ++col;
    }
    return false;
}

bool Game::checkWinVerticalDown() { // '\'
        int nbrAdjCell = 0;
        for (int row = 0; row < ROW; ++row){
        for (int col = 0; col < COL; ++col) { // On itére dans chaque colonne dans la ligne actuel
            const Game::Player& valPlayer = _grid[row][col]; // Récupére la valeur actuelle
            if (valPlayer == _currentPlayer && row == col) {
                ++nbrAdjCell;
                if (nbrAdjCell == ROW){
                    _state = (_currentPlayer == Player::PLAYER_1) ? GameState::PLAYER_1_WIN : GameState::PLAYER_2_WIN;
                    return true;
                }
            }
        }
    }
    return false;
        /*    X * *   [0][0]
        *    * X *    [1][1]
        *    * * X    [2][2]*/
    }

