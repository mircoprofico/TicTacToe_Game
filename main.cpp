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
    cout << endl;

    const int row = 3;
    const int col = 3;

    Game game(row,col);
    Display display(game);
    display.run();
    cout << endl;

    return EXIT_SUCCESS;
}
