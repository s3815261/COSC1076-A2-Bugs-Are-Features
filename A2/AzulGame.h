#ifndef __AZULGAME__
#define __AZULGAME__

#include "tileBag.h"
#include "player.h"

class AzulGame 
{
    public:
        AzulGame();
        ~AzulGame();
        std::string getP1();
        std::string getP2();
        TileBag getTB();

    private:
        TileBag tb;
        Player p1;
        Player p2;
};

#endif