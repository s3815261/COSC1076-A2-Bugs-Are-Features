#ifndef __AZULGAME__
#define __AZULGAME__

#include <vector>

#include "TileBag.h"
#include "Player.h"
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
        Factory* getBroken();
        std::vector<std::string> getTurns();

        void setPlayerNames(std::string playerNameArray[]);
        
        void addTurn(std::string turn);
        void populateFactories();
        bool factoriesIsEmpty();
        void printPlayerNames();
        void newGame();
        void loadGame();
        void playGame();
        void printPlayer1Board(bool player1Turn);
        void printFactories();
        bool checkCommandIsValid(std::string input);
        void runCommand(std::string input, bool player1Turn);
        void takeFirstPlayerToken(bool player1Turn);
        void endOfRound();
        void calculateScore(bool player1Turn);

    private:
        TileBag* tileBag;
        Player** players;
        Factory** factories;
        Factory* broken;
        std::vector<std::string> turnVector;
        int roundNumber;
        int turnNumber;
};

#endif