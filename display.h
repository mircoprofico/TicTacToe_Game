#ifndef TICTACTOE_DISPLAY_H
#define TICTACTOE_DISPLAY_H

#include "game.h"

class Display {
public:
    Display(const Game& game);
    void run();

private:
    Game game;
    const size_t ROW = game.getRow();
    const size_t COL = game.getCol();

    bool appIsRunning;

    void displayGrid(size_t row, size_t col);
};


#endif //TICTACTOE_DISPLAY_H
