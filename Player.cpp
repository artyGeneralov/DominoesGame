#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "Player.h"
#include "Pile.h"
#include <iostream>
#include <cassert>
#include <string.h>
using namespace std;

Player::Player(const char* name, bool isHuman)
{
    this->isHuman = isHuman;
    setName(name);
}

Player::Player(const Player& player)
{
    // copy name
    this->name = new char[strlen(player.name) + 1];
    assert(name != 0);
    strcpy(this->name, player.name);
    // copy pile size
    this->pileSize = player.pileSize;
    // copy pile
    this->playerPile = *(new Pile(player.playerPile));
    // copy isHuman
    this->isHuman = player.isHuman;
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


Player Player::operator=(Player pl)
{
    if(name != 0)
        delete[] name;
    name = new char[strlen(pl.name) + 1];
    assert(name != 0);
    strcpy(name, pl.name);

    pileSize = pl.pileSize;
    
    playerPile = pl.playerPile;
    isHuman = pl.isHuman;

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