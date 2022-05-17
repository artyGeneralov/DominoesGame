#ifndef GAME_H
#define GAME_H
#include "Player.h"

class Game{
    private:
        Player humanPlayer, computerPlayer;
        Pile fullDeck, tablePile;
        int leftEdge, rightEdge;

        bool isOver();  // Check whether a victory or loss condition has been achieved
        bool hasLegalMove(Player); // Check if a player has legal moves
        void startUpPlayerHand(Player); // Start up a hand with 7 cards

    public:
        Game();
        void printBoard();
        void runGame();

};

#endif