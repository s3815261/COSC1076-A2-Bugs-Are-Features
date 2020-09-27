#ifndef __AZULGAME__
#define __AZULGAME__

#include "tileBag.h"
#include "player.h"
#include "vector"

class AzulGame 
{
    public:
        AzulGame();
        ~AzulGame();
        std::string getP1Name();
        std::string getP2Name();
        tileBag* getTB();
        void setP1Name(std::string);
        void setP2Name(std::string);
        void printNames();
        void addTurn(Turn turn);

    private:
        TileBag tb;
        Player p1;
        Player p2;
        std::vector<Turn> turn_vector;

};

#endif