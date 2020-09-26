#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
#include "playerboard.h"

class player
{
public:
    player();
    ~player();
    std::string getName();

private:
    std::string name;
    int score;
    playerBoard pB;
};
#endif