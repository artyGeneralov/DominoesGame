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
    if (tablePile != 0)
        delete(tablePile);
    if (fullDeck != 0)
        delete(fullDeck);
    if (humanPlayer != 0)
        delete(humanPlayer);
    if (computerPlayer != 0)
        delete(computerPlayer);
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
    cout << "\n";
    for(int i = 0; i < computerPlayer->getPileSize(); i++)
        cout << " -- " << i << " - ";
    

    // Main Board:
    cout << "\n\n";
    tablePile->printOpen();
    cout << "\n\n";

    // Player Side:
    cout << "******" << humanPlayer->getPlayerName() << "******\n";
    humanPlayer->getPlayerPile().printOpen();
    cout << "\n";
    for(int i = 0; i < humanPlayer->getPileSize(); i++)
        cout << " -- " << i << " - ";
    
}

void Game::startUpPlayerHand(Player& p)
{

    for(int i = 0; i < 7; i++)
       p.addStone(fullDeck->removeStone(0));
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
    Game* game = new Game();
    game->printBoard();

   /* Player* humanPlayer = new Player("HUMANsss", true);

    Player* computerPlayer = new Player("COMPUTER", false);
    
    Pile* fullDeck = new Pile();
    fullDeck->fillPile();
    fullDeck->shufflePile();


    for(int i = 0; i < 7; i++)
        humanPlayer->addStone(fullDeck->removeStone(0));

    humanPlayer->printPile();
    cout << "\nPILE\n";
    fullDeck->printOpen();*/
   

    /*Pile* fullDeck = new Pile();
    fullDeck->fillPile();
    fullDeck->shufflePile();
    fullDeck->printOpen();

    Pile* tablePile = new Pile();


    
    if (humanPlayer != 0)
        delete(humanPlayer);
    /*if (computerPlayer != 0)
        delete(computerPlayer);*/
   /* if (tablePile != 0)
        delete(tablePile);
    delete(fullDeck);*/


    /*Player p("Player", true);
    p.addStone(Stone(1, 1));
    p.addStone(Stone(2, 2));
    p.printPile();*/
   // cout << p.getPileSize();


    /*Pile p1, p2, p3, p4;
    p1.fillPile();
    p1.shufflePile();
    p1.printOpen();
    cout << "\n**********\n";
    p2.fillPile();
    p2.printOpen();
    cout << "\n**********\n";
    p3.fillPile();
    p3.printOpen();
    cout << "\n**********\n";
    p4.fillPile();
    p4.printOpen();*/
}