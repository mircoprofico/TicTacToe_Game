#include <iostream>
#include <cstdlib>
#include <vector>
#include "game.h"
#include "display.h"

using namespace std;

enum class Player {
    NONE,
    PLAYER1,
    PLAYER2
};

int main() {
    cout << "Jeu du TicTacToe" << endl;

    const int ROW = 3;
    const int COL = 3;

    Game game(ROW, COL);
    Display display(game);
    display.run();
    cout << endl;

    return EXIT_SUCCESS;
}
