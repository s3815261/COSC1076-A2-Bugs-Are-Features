#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
#include "playerboard.h"

class player {
    public:
    player();
    
    private:
        std::string name;
        int score;
        playerBoard pB;
};
#endif