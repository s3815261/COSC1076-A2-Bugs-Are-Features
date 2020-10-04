#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>

#include "PlayerBoard.h"
#include "Factory.h"

class Player
{
public:
    Player(std::string name);
    ~Player();

    std::string getName();
    void setName(std::string);
    int getScore();
    void setScore(int score);
    
    PlayerBoard* getPlayerBoard();
    void printBoard();

private:
    std::string name;
    int score;
    PlayerBoard* playerBoard;

};
#endif // __PLAYER__