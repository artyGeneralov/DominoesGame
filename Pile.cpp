#ifndef PILE_CPP
#define PILE_CPP


#include "Pile.h"
#include "Stone.h"
#include <cassert>
#include <iostream>
#include <time.h>
using namespace std;

Pile::Pile()
{
    stones_array = new Stone[0];
    pileSize = 0;
}


Pile::Pile(const Pile& pile)
{
    
    stones_array = new Stone[pile.pileSize];
    for (int i = 0; i < pile.pileSize; i++)
        stones_array[i] = *(new Stone(pile.stones_array[i].getLeft(), pile.stones_array[i].getRight()));
    this->pileSize = pile.pileSize;
}


Stone Pile::stoneByIndex(int index)
{
    if(index > pileSize || index < 0)
    {
        cout << "Wrong index!"<< endl;
        exit(0);
    }

    Stone s = *(new Stone(stones_array[index].getLeft(), stones_array[index].getRight()));
    return s;
}

const void Pile::printOpen()
{
    for(int i = 0; i < pileSize; i++)
    {
        stones_array[i].printOpen();
        cout << ", ";
    }
    
}

const void Pile::printClosed()
{
    for(int i = 0; i < pileSize; i++)
        stones_array[i].printClosed();
}

void Pile::fillPile()
{
    const int MAX_SIZE = 6;
    for(int i = 0; i <=MAX_SIZE; i++)
        for(int j = 0; j <= i; j++)
        {
            Stone* newStone = new Stone(i,j);
            addStone(*newStone, Stone::Right);
        }
}

void Pile::shufflePile()
{

    srand(time(0));
    int randIndex;
    Stone* newStoneArr = new Stone[pileSize];
    for(int i = 0; i < pileSize; i++)
    {
        // 1. Pick random index
        randIndex = rand() % MAX_PILE_SIZE + 1;
        // 2. if theres a Stone there add it to the next place in a new array
        if(this->stones_array[randIndex].getLeft() != -1)
        {
            newStoneArr[i] = stones_array[randIndex];
            stones_array[randIndex] = *(new Stone(-1,-1));
        }
        else
        {
            // 3. if there isnt a number there, search to the right then search to the left until you find a number
            // Look Right:
            int j = randIndex + 1;
            while(j < pileSize && this->stones_array[j].getLeft() == -1)
                j++;
            if(j == pileSize)
            {
                // Look Left:
                j = randIndex - 1;
                while( j > 0 && this->stones_array[j].getLeft() == -1)
                    j--;
            }
            newStoneArr[i] = *new Stone(stones_array[j].getLeft(), stones_array[j].getRight());
            stones_array[j] = *(new Stone(-1,-1));
        }
    }
    delete[] stones_array;
    this->stones_array = newStoneArr;
    newStoneArr = NULL;
}

void Pile::addStone(Stone stoneToAdd, Stone::side side)
{
    if(pileSize == MAX_PILE_SIZE)
    {
        cout << "Can't add additional stones!" << endl;
        exit(0);
    }

    pileSize++;         // Incrementing the pile size off the get go
    Stone* newStoneArr = new Stone[pileSize];
    assert(newStoneArr!=0);
    int i = 0;
    if(side == Stone::Left)
    {
        // Add to left side:
        newStoneArr[0] = stoneToAdd;
        i++;  
        for(; i < pileSize; i++)
            newStoneArr[i] =*(new Stone(stones_array[i-1].getLeft(), stones_array[i-1].getRight()));
    }
    else
    {
        // Add to rigth side:
        for(; i < pileSize - 1; i++){
            newStoneArr[i] =*(new Stone(stones_array[i].getLeft(), stones_array[i].getRight()));
        }
        newStoneArr[i] = stoneToAdd;

    }
    //Stone* ------ Stone*
    delete[] stones_array;
    stones_array = newStoneArr;
    newStoneArr = NULL;
}

Stone Pile::removeStone(int index)
{
    if(pileSize == 0 || index < 0 || index > pileSize)
    {
        cout << "Illegal removal request\n";
        exit(0);
    }
    
    Stone removed = *(new Stone(stones_array[index].getLeft(), stones_array[index].getRight()));
    Stone* newStoneArr = new Stone[pileSize - 1];
    assert(newStoneArr!= 0);

    int j = 0;
    for(int i = 0; i < pileSize - 1; i++, j++)
    {
        if(i == index)
            j++;
        newStoneArr[i] = *(new Stone(stones_array[j].getLeft(), stones_array[j].getRight()));
    }
    
    pileSize--;
    delete[] stones_array;
    stones_array = newStoneArr;
    newStoneArr = NULL;
    return removed;
}

Stone* Pile::getStonesArray()
{
    Stone* newStonesArr = new Stone[pileSize];
    for(int i = 0; i < pileSize; i++)
        newStonesArr[i] =*( new Stone(stones_array[i].getLeft(), stones_array[i].getRight()));
    return newStonesArr;
}

Pile Pile::operator=(Pile p)
{
    delete[] this->stones_array;
    this->pileSize = p.getPileSize();
    this->stones_array = p.getStonesArray();
    return *this;
}

bool Pile::isEmpty()
{
    return pileSize == 0;
}


#endif