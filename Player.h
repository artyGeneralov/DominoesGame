#ifndef PLAYER_H
#define PLAYER_H
#include "Pile.h"
#include "Stone.h"


class Player
{
    private:
        char* name;
        int pileSize = STARTING_PILE_SIZE;
        Pile* playerPile;
        bool isHuman;

    public:
        const int STARTING_PILE_SIZE = 7;
        Player() {
            name = new char[0];
            playerPile = new Pile();
            pileSize = 0;
            isHuman = true;
        }
        Player(const Player&); // copy constructor
        Player(const char*, bool); // args (Name, isHuman)
        ~Player() { delete[] name; delete[] playerPile; }
        const int getPileSize(){return this->pileSize;};
        char* getPlayerName(){return this->name;};
        void setName(const char*); // name
        void setPile(Pile pile); // set Pile
        const Stone removeStone(const int); // index
        void addStone(Stone); // stoneToAdd
        Pile getPlayerPile();
        Player operator=(Player pl);

        


};

#endif