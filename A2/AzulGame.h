#ifndef __AZULGAME__
#define __AZULGAME__

#include <vector>

#include "TileBag.h"
#include "Player.h"
#include "Util.h"

class AzulGame 
{
    public:
        AzulGame();
        ~AzulGame();
        std::string getPlayer1Name();
        std::string getPlayer2Name();
        TileBag* getTileBag();
        void setPlayer1Name(std::string player1Name);
        void setPlayer2Name(std::string player2Name);
        void printPlayerNames();
        void addTurn(Turn turn);

    private:
        TileBag* tileBag;
        Player player1;
        Player player2;
        std::vector<Turn> turn_vector;

};

#endif