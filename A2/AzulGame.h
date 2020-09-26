#ifndef __AZULGAME__
#define __AZULGAME__

#include "tileBag.h"
#include "player.h"

class azulGame{
    public:
        azulGame();
        ~azulGame();
        std::string getP1();
        std::string getP2();
        tileBag getTB();
    private:
        tileBag tb;
        player p1;
        player p2;
};

#endif