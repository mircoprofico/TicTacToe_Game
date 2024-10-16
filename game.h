#ifndef TICTACTOE_GAME_H
#define TICTACTOE_GAME_H

#include <iostream>
#include <vector>
using uint = unsigned int;

class Game {
public:
    Game();//Constructor by default 3 - 3
    Game(size_t row, size_t col); //Constructor with ROW and COL

    enum class GameState {
        IN_PROGRESS,
        PLAYER_1_WIN,
        PLAYER_2_WIN,
        DRAW };
    enum class Player {
        NONE,
        PLAYER_1,
        PLAYER_2 };

    using Grid = std::vector<std::vector<Player>>;

    [[nodiscard]] size_t getRow() const;
    [[nodiscard]] size_t getCol() const;
    [[nodiscard]] GameState getStatus() const;
    [[nodiscard]] Player getPlayer() const;
    [[nodiscard]] Player getCell(size_t r, size_t c) const;
    [[nodiscard]] bool isRunning() const;

    void play();
    bool isGameOver(); 
    Grid _grid;


private:
    const int ROW;
    const int COL;

    bool _appIsRunning;
    GameState _state;
    Player _currentPlayer;
    size_t _nbOfPlay;

    void makeMove(Player whichPlayer); 
    void displayPositionOnTheGrid(uint pos1, uint pos2); 
    Player changePlayer(); 
    [[nodiscard]] bool checkWinRow();
    [[nodiscard]] bool checkWinCol();
    [[nodiscard]] bool checkWinVerticalUp();
    [[nodiscard]] bool checkWinVerticalDown();


};

#endif //TICTACTOE_GAME_H
