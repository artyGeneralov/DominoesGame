#ifndef PLAYER_H
#define PLAYER_H
#include "Pile.h"
#include "Stone.h"


class Player
{
    private:
        char* name;
        int pileSize = STARTING_PILE_SIZE;
        Pile playerPile = *(new Pile());
        bool isHuman;

    public:
        const int STARTING_PILE_SIZE = 7;
        Player(){};
        Player(const char*, bool); // Name, isHuman
        ~Player(){delete[] name;}
        const int getPileSize(){return this->pileSize;};
        char* getPlayerName(){return this->name;};
        void setName(const char*); // name
        void setPile(Pile pile); // set Pile
        const Stone removeStone(const int); // index
        void addStone(Stone); // stoneToAdd
        Pile getPlayerPile();
        Player &operator=(Player &pl);

        


};

#endif