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
    for(int i = 0; i < computerPlayer->getPlayerPile().getPileSize(); i++)
        cout << " - " << i+1 << " -  ";
    

    // Main Board:
    cout << "\n\n\n";
    tablePile->printOpen();
    cout << "\n\n\n";

    // Player Side:
    cout << "****** " << humanPlayer->getPlayerName() << " ******\n";
    humanPlayer->getPlayerPile().printOpen();
    cout << "\n";
    for(int i = 0; i < humanPlayer->getPlayerPile().getPileSize(); i++)
        cout << " - " << i+1 << " -  ";
    
}

// Game Manager:

void Game::runGame()
{
    // 1.) check whose turn it is
    // first turn is whoever has a 6-6 and else its the player


    // TEST:
    printBoard();
    for (int i = 0; i < 8; i++) {
        humanTurn();
        cout << "\n\n\n************************** " << "Left edge: " << leftEdge << "Right edge:" << rightEdge;
        cout << "***********************\n\n\n";
        
        printBoard();
    }
    

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
    if (tablePile->getPileSize() == 0)
        return true;
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

void Game::computerTurn() {
    cout << "\nIt's the computers turn.\n";
    // No legal moves -> either grab from the bank or pass the turn.
    bool hasLegal = hasLegalMove(*computerPlayer);
    bool bankEmpty = bankPile->isEmpty();
    if (!hasLegal && !bankEmpty){
        computerPlayer->addStone(bankPile->removeStone(0));
        return;
    }
    else if (!hasLegal && bankEmpty) {
        cout << "Computer player has no move.\n";
        return;
    }

    int indexToPlay;
    
    // 
    // Find the best move:

    // Best move is double
    // next best is the highest sum

}


void Game::humanTurn() {
    cout << "\nIt's your turn, \n" << humanPlayer->getPlayerName() << "!\n";
    
    // No legal moves -> grab from bank if possible and pass turn.
    bool hasLegal = hasLegalMove(*humanPlayer);
    bool bankEmpty = bankPile->isEmpty();
    if (!hasLegal && !bankEmpty) {
        cout << "\nYou have no legal moves. A stone will be added to your hand.\nPress \"enter\" to pass:";
        cin.ignore();
        humanPlayer->addStone(bankPile->removeStone(0));
        return;
    }
    else if (!hasLegal && bankEmpty) {
        cout << "\nYou have no legal moves. The bank pile is empty.\nPress \"enter\" to pass:";
        cin.ignore();
        return;
    }

    // Play turn
    int stoneIndex;
    while (true) {
        cout << "\nPlease pick the index of a stone to place on the board: ";
        cin >> stoneIndex;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (stoneIndex < 1 ||           // Wrong index
            stoneIndex > humanPlayer->getPileSize() ||
            !isStoneLegal(humanPlayer->getPlayerPile().getStonesArray()[stoneIndex-1])) // Stone is illegal
        {
            cout << "\nOops! Wrong stone index! Try Again.";
            continue;
        }
        break;
    }
    stoneIndex--; // Board starts at 1 while index starts at 0

    
    int stoneLeft = humanPlayer->getPlayerPile().getStonesArray()[stoneIndex].getLeft();
    int stoneRight = humanPlayer->getPlayerPile().getStonesArray()[stoneIndex].getRight();
    // If the table is empty, just place the stone and end.
    if (tablePile->getPileSize() == 0) {
        tablePile->addStone(humanPlayer->removeStone(stoneIndex), Stone::Right);
        leftEdge = stoneLeft;
        rightEdge = stoneRight;
        return;
    }

    // If the stone can be played on both sides
    if ((stoneLeft == leftEdge && stoneLeft == rightEdge) ||
        (stoneLeft == leftEdge && stoneRight == rightEdge) ||
        (stoneRight == leftEdge && stoneRight == rightEdge) ||
        (stoneRight == leftEdge && stoneLeft == rightEdge))
    {
        int c; // Choice of side
        while (true) {
            // Ask the player which side he wants to play.
            cout << "\nThe stone you have chosen can be played on both sides. Which side would you like?\n";
            cout << "1 - left   <--  -->   2 - right\n";
        
            // Ask again ?
            cin >> c;
            if (c != 1 && c != 2) {
                cout << "Oops. Input 1 or 2 only! Try Again.";
                continue;
            }
            break;
        }
        switch (c) {
            case 1: // Rotate & Place on Left
                if (stoneLeft != stoneRight && stoneLeft == leftEdge)
                    humanPlayer->getPlayerPile().getStoneArrayPtr()[stoneIndex].rotateStone();
                tablePile->addStone(humanPlayer->getPlayerPile().removeStone(stoneIndex), Stone::Left);
                leftEdge = tablePile->getStonesArray()[0].getLeft();
                
                break;
            case 2: // Rotate & Placce on Right
                if (stoneLeft != stoneRight && stoneLeft == leftEdge)
                    humanPlayer->getPlayerPile().getStoneArrayPtr()[stoneIndex].rotateStone();
                tablePile->addStone(humanPlayer->getPlayerPile().removeStone(stoneIndex), Stone::Right);
                rightEdge = tablePile->getStonesArray()[tablePile->getPileSize() - 1].getRight();
                
                break;
        }
    }
    else{
        // Rotate stone if needed
        if (stoneLeft == leftEdge || stoneRight == rightEdge)
            humanPlayer->getPlayerPile().getStonesArray()[stoneIndex].rotateStone();
        // Play on the correct side
        if (stoneRight == leftEdge) {
            tablePile->addStone(humanPlayer->getPlayerPile().removeStone(stoneIndex), Stone::Left);
            leftEdge = tablePile->getStonesArray()[0].getLeft();
        }
        else{
            tablePile->addStone(humanPlayer->getPlayerPile().removeStone(stoneIndex), Stone::Right);
            rightEdge = tablePile->getStonesArray()[tablePile->getPileSize() - 1].getRight();
        }
    }
}


int main()
{
    Game* game = new Game("Harry");
    game->runGame();

}