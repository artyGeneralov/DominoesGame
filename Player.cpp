#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "Player.h"
#include "Pile.cpp"
#include <iostream>
#include <string.h>
using namespace std;

Player::Player(const char* name, bool isHuman)
{
    this->isHuman = isHuman;
    setName(name);
}

void Player::setName(const char* name){
    this->name = new char(strlen(name)+1);
    assert(name);
    strcpy(this->name, name);
    *(this->name + sizeof(char) * strlen(this->name)) = '\0';
}


const Stone Player::removeStone(const int index)
{
    Stone removedStone = this->playerPile.removeStone(index);
    this->pileSize--;
    return removedStone;
}


void Player::addStone(Stone stoneToAdd)
{
    this->playerPile.addStone(stoneToAdd, Stone::Right);
    this->pileSize++;
}


Player &Player::operator=(Player& pl)
{
    if(&pl != this)
    {
        this->setName(pl.getPlayerName());
    }

    return *this;
}

Pile Player::getPlayerPile()
{
    Pile newPile = this->playerPile;
    return newPile;
}

void Player::setPile(Pile pile)
{
    
}

#endif