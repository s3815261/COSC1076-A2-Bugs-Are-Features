#ifndef __AZULGAME__
#define __AZULGAME__

#include <vector>

#include "TileBag.h"
#include "Player.h"
#include "Util.h"
#include "Factory.h"
#include "Tile.h"

#define NUM_FACTORIES   6

class AzulGame 
{
    public:
        AzulGame();
        ~AzulGame();
        std::string getPlayer1Name();
        std::string getPlayer2Name();
        TileBag* getTileBag();
        PlayerBoard* getPlayerBoard();
        Factory** getFactories();
        void setPlayer1Name(std::string player1Name);
        void setPlayer2Name(std::string player2Name);
        std::vector<std::string> getTurns();
        
        void addTurn(std::string turn);
        void populateFactories();
        void printPlayerNames();
        void newGame();
        void loadGame();
        void playGame();
        void printBoard(bool player1Turn);
        void printFactories();
        void runCommand(std::string input, bool player1Turn);

    private:
        TileBag* tileBag;
        Player* player1;
        Player* player2;
        Factory** factories;
        std::vector<std::string> turn_vector;
        int turn_number;

};

#endif