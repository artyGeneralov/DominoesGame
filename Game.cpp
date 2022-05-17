#include "Pile.cpp"
#include "Game.h"
#include "Player.cpp"
#include <iostream>
using namespace std;

Game::Game()
{
    this->humanPlayer = *(new Player("HUMAN", true));
    this->computerPlayer = *(new Player("COMPUTER", false));

    this->fullDeck = *(new Pile());
    this->fullDeck.fillPile();
    this->fullDeck.shufflePile();

    this->tablePile = *(new Pile());

    startUpPlayerHand(humanPlayer);
    startUpPlayerHand(computerPlayer);
}

bool Game::hasLegalMove(Player p)
{
    for(int i = 0; i < p.getPileSize(); i++)
        if(p.getPlayerPile().getStonesArray()->Right == leftEdge
            ||p.getPlayerPile().getStonesArray()->Right == rightEdge
            ||p.getPlayerPile().getStonesArray()->Left == leftEdge
            ||p.getPlayerPile().getStonesArray()->Left == rightEdge)
                return true;
    return false;
}

void Game::printBoard()
{
    cout << "K U P A\nstart-->";
    fullDeck.printClosed();
    cout << "<--end\n";

    // Computer Side:
    cout << "******" << computerPlayer.getPlayerName() << "******\n";
    computerPlayer.getPlayerPile().printClosed();
    for(int i = 0; i < computerPlayer.getPileSize(); i++)
        cout << " --- " << i << " --- ";
    

    // Main Board:
    cout << "\n\n";
    tablePile.printOpen();
    cout << "\n\n";

    // Player Side:
    cout << "******" << humanPlayer.getPlayerName() << "******\n";
    humanPlayer.getPlayerPile().printOpen();
    for(int i = 0; i < humanPlayer.getPileSize(); i++)
        cout << " --- " << i << " --- ";
    
}

void Game::startUpPlayerHand(Player p)
{
    Pile pile = *(new Pile());
    for(int i = 0; i < 7; i++){
        pile.addStone(fullDeck.removeStone(0), Stone::Right);
    }
    
}

bool Game::isOver()
{
    if(this->humanPlayer.getPlayerPile().isEmpty() ||
        this->computerPlayer.getPlayerPile().isEmpty() || 
        (!hasLegalMove(this->humanPlayer) && !hasLegalMove(this->computerPlayer) && fullDeck.isEmpty()))
            return true;
    return false;
}


int main()
{
    Game game;
    game.printBoard();
}