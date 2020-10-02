#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
#include "PlayerBoard.h"

class Player
{
public:
    Player(std::string name);
    ~Player();
    std::string getName();
    void setName(std::string);
    int getScore();
    void setScore(int score);
    void addScore(int increment);
    PlayerBoard* getPlayerBoard();

private:
    std::string name;
    int score;
    PlayerBoard* playerBoard;

};
#endif // __PLAYER__