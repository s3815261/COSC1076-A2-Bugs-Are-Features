#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
#include "playerboard.h"

class Player
{
public:
    Player();
    Player(std::string name);
    Player(std::string name, int score);
    ~Player();
    std::string getName();
    void setName(std::string);

private:
    std::string name;
    int score;
    PlayerBoard pB;

};
#endif // __PLAYER__