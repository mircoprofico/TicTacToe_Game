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

int main(int argc, char* argv[]) {

    // Pour lancer le jeu utiliser le terminal :
    // g++ main.cpp game.cpp display.cpp -o main
    // ./main 3 3

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <nombre de lignes> <nombre de colonnes>" << std::endl;
        return EXIT_FAILURE;
    }
    // Convertit les arguments du terminal en entiers pour les dimensions
    int row = std::stoi(argv[1]);
    int col = std::stoi(argv[2]);

    if (row <= 0 || col <= 0) {
        std::cerr << "Les dimensions de la grille doivent être des entiers positifs." << std::endl;
        return EXIT_FAILURE;
    }
    cout << "Jeu du TicTacToe" << endl;


    Game game(row, col);
    Display display(game);
    display.run();
    cout << endl;

    return EXIT_SUCCESS;
}
