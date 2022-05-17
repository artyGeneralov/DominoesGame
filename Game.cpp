#include "Pile.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
using namespace std;

Game::Game()
{
    humanPlayer = new Player("HUMAN", true);

    computerPlayer = new Player("COMPUTER", false);

    fullDeck = new Pile();
    fullDeck->fillPile();
    fullDeck->shufflePile();

    tablePile = new Pile();

    startUpPlayerHand(*humanPlayer);
    startUpPlayerHand(*computerPlayer);
}

Game::~Game()
{
    delete[] humanPlayer, computerPlayer, fullDeck, tablePile;
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
    fullDeck->printClosed();
    cout << "<--end\n";

    // Computer Side:
    cout << "******" << computerPlayer->getPlayerName() << "******\n";
    computerPlayer->getPlayerPile().printClosed();
    for(int i = 0; i < computerPlayer->getPileSize(); i++)
        cout << " --- " << i << " --- ";
    

    // Main Board:
    cout << "\n\n";
    tablePile->printOpen();
    cout << "\n\n";

    // Player Side:
    cout << "******" << humanPlayer->getPlayerName() << "******\n";
    humanPlayer->getPlayerPile().printOpen();
    for(int i = 0; i < humanPlayer->getPileSize(); i++)
        cout << " --- " << i << " --- ";
    
}

void Game::startUpPlayerHand(Player p)
{
    Pile pile = *(new Pile());
    for(int i = 0; i < 7; i++)
        pile.addStone(fullDeck->removeStone(0), Stone::Right);
}

bool Game::isOver()
{
    if(humanPlayer->getPlayerPile().isEmpty() ||
        computerPlayer->getPlayerPile().isEmpty() ||
        (!hasLegalMove(*humanPlayer) && !hasLegalMove(*computerPlayer) && fullDeck->isEmpty()))
            return true;
    return false;
}


int main()
{
    //Game game;
    //game.printBoard();
    Pile p;
    p.fillPile();
    p.shufflePile();
    p.printOpen();
}