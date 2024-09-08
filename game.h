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
    bool isGameOver(); // Vérifie l'état actuel du jeu
    Grid _grid;


private:
    const size_t ROW;
    const size_t COL;

    bool _appIsRunning;
    GameState _state;
    Player _currentPlayer;
    size_t _nbOfPlay;

    void makeMove(Player whichPlayer); // Fonction qui va demander au user de choisir une position sur la grille et controler si déja occuper ensuite va appeler fonction display position
    void displayPositionOnTheGrid(uint pos1, uint pos2); // Va afficher la position voulu dans la grille
    Player changePlayer(); // fonction switch à la fin de chaque coup, chaque fois que selectposition
    [[nodiscard]] bool checkWinRow() const;
    [[nodiscard]] bool checkWinCol() const;
    [[nodiscard]] bool checkWinVerticalUp() const;
    [[nodiscard]] bool checkWinVerticalDown() const;


};

#endif //TICTACTOE_GAME_H


/*
 * début
 * affichage grille
 * fonction makeMove() activé : va demander au user1 de donner 2 positions
 * displayPosition() : va afficher dans la grille
 * Check ligne
 * changePlayer();
 * makeMove()
 * displayPosition()
 * checkLigne quand compteur nb de round = 3
 * isGameOver()  ?
 * true -> appIsRunning = false
 * false -> changePlayer()
 */

// TODO Mise en place d'un compteur de nombre de round jusqu'à 3 et ensuite check de isGameOver ?
// TODO Check entrée utilisateur POSition