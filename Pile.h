#ifndef PILE_H
#define PILE_H
#include "Stone.h"

class Pile
{
    private:
        Stone* stones_array;
        int pileSize;
        const int MAX_PILE_SIZE = 28;
        

    public:
        Pile();
        Pile(const Pile&);
        ~Pile() {delete[] stones_array;}
        Stone stoneByIndex(int);
        const void printOpen();
        const void printClosed();
        void fillPile();
        void shufflePile();
        void addStone(Stone, Stone::side);
        const int getPileSize(){return this->pileSize;}

        bool isEmpty();
        
        Stone* getStonesArray();
        Stone removeStone(int);
        Pile operator=(Pile);
};

#endif