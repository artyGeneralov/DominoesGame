#ifndef STONE_CPP
#define STONE_CPP

#include "Stone.h"
#include <iostream>
using namespace std;


Stone::Stone(int left, int right){
    this->right = right;
    this->left = left;
}

void Stone::rotateStone()
{
    int temp = this->right;
    this->right = this->left;
    this->left = temp;
}


const bool Stone::compareStones(Stone s2)
{
    return (this->right == s2.getRight()) ||
            (this->right == s2.getLeft()) ||
            (this->left == s2.getRight()) ||
            (this->left == s2.getLeft());
}

const void Stone::printOpen()
{
    cout << "[" << this->getLeft() 
    << "]["<<this->getRight() << "]";

}
const void Stone::printClosed()
{
    cout << "[][]";
}

#endif