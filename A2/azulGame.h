#ifndef __AZULGAME__
#define __AZULGAME__

#include "tileBag.h"
#include "boxLid.h"
#include "player.h"

class azulGame{
    public:
        azulGame(){};
        ~azulGame(){};
        tileBag tb;
        boxLid bl;
        player p1;
        player p2;
    private:
        
};

#endif