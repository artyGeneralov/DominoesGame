#ifndef STONE_H
#define STONE_H

class Stone{
    private:
        int right=-1, left=-1; 

    public:
        Stone() {};
 // Empty Constructor
        Stone(int, int);
        int getRight(){return right;}
        int getLeft(){return left;}
        void rotateStone();
        const bool compareStones(Stone s2);
        const void printOpen();
        const void printClosed();
        enum side{Left = 0, Right};
};
#endif