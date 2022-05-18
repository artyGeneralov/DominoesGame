#include "Pile.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
using namespace std;

// C/D:

// Main constructor. Initializes a Human and Computer players
Game::Game(const char* humanName)
{
    humanPlayer = new Player(humanName, true);

    computerPlayer = new Player("COMPUTER", false);

    bankPile = new Pile();
    bankPile->fillPile();
    bankPile->shufflePile();

    tablePile = new Pile();

    startUpPlayerHand(*humanPlayer);
    startUpPlayerHand(*computerPlayer);
    leftEdge = rightEdge = -1;
}

Game::~Game()
{
    if (tablePile != 0)
        delete(tablePile);
    if (bankPile != 0)
        delete(bankPile);
    if (humanPlayer != 0)
        delete(humanPlayer);
    if (computerPlayer != 0)
        delete(computerPlayer);
}



// Printer:
void Game::printBoard()
{
    cout << "K U P A\nstart-->";
    bankPile->printClosed();
    cout << "<--end\n";

    // Computer Side:
    cout << "****** " << computerPlayer->getPlayerName() << " ******\n";
    computerPlayer->getPlayerPile().printClosed();
    cout << "\n";
    for(int i = 0; i < computerPlayer->getPileSize(); i++)
        cout << " -- " << i << " - ";
    

    // Main Board:
    cout << "\n\n";
    tablePile->printOpen();
    cout << "\n\n";

    // Player Side:
    cout << "****** " << humanPlayer->getPlayerName() << " ******\n";
    humanPlayer->getPlayerPile().printOpen();
    cout << "\n";
    for(int i = 0; i < humanPlayer->getPileSize(); i++)
        cout << " -- " << i << " - ";
    
}

// Game Manager:

void Game::runGame()
{
    // 1.) check whose turn it is
    // first turn is whoever has a 6-6 and else its the player

}


// Private helper methods:

// true if player @p has any legal moves, else false
bool Game::hasLegalMove(Player p) {
    for (int i = 0; i < p.getPileSize(); i++)
        if (isStoneLegal(p.getPlayerPile().getStonesArray()[i]))
            return true;
    return false;
}

// true if a Stone @stone can be placed on the table, else false
bool Game::isStoneLegal(Stone stone) {
    if (stone.getLeft() == leftEdge ||
        stone.getRight() == leftEdge ||
        stone.getLeft() == rightEdge ||
        stone.getRight() == rightEdge)
        return true;
    return false;
}

// Method to fill a players hand with 7 cards from the bankPile, must be run at the beginning of a game
void Game::startUpPlayerHand(Player& p){

    for (int i = 0; i < 7; i++)
        p.addStone(bankPile->removeStone(0));
}

// returns true if any player has an empty hand, or both players have no moves and the bank is empty
// else false
bool Game::isOver(){
    if (humanPlayer->getPlayerPile().isEmpty() ||
        computerPlayer->getPlayerPile().isEmpty() ||
        (!hasLegalMove(*humanPlayer) && !hasLegalMove(*computerPlayer) && bankPile->isEmpty()))
        return true;
    return false;
}


void computerTurn() {
    // Assuming there is a legal move.
}





int main()
{
    Game* game = new Game("Harry");
    game->printBoard();

}