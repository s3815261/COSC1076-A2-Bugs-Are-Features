#ifndef __AZULGAME__
#define __AZULGAME__

#include <vector>

#include "TileBag.h"
#include "Player.h"
#include "Util.h"
#include "Factory.h"
#include "Tile.h"

#define NUM_PLAYERS     2
#define NUM_FACTORIES   6
#define PLAYER1_INDEX   0
#define PLAYER2_INDEX   1

class AzulGame 
{
    public:
        AzulGame();
        ~AzulGame();
        TileBag* getTileBag();
        PlayerBoard* getPlayerBoard();
        Player** getPlayers();
        Factory** getFactories();
        std::vector<std::string> getTurns();

        void setPlayerNames(std::string playerNameArray[]);
        
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
        Player** players;
        Factory** factories;
        std::vector<std::string> turn_vector;
        int turn_number;

};

#endif