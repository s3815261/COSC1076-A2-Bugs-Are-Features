#ifndef __AZULGAME__
#define __AZULGAME__

#include <vector>

#include "TileBag.h"
#include "Player.h"
#include "Factory.h"
#include "Tile.h"

#define NUM_PLAYERS             2
#define NUM_FACTORIES           6
#define CENTRAL_FACTORY_INDEX   0
#define PLAYER1_INDEX           0
#define PLAYER2_INDEX           1
#define MAX_BROKEN              7

#define RED                     'R'
#define YELLOW                  'Y'
#define DARK_BLUE               'B'
#define LIGHT_BLUE              'L'
#define BLACK                   'U'

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
        bool factoriesIsEmpty();
        void printPlayerNames();
        void newGame();
        void loadGame();
        void playGame();
        void nextPlayerTurn();
        void printPlayerGameBoard();
        void printFactories();
        bool isCommandValid(std::string input);
        bool isValidTile(char tileChar);
        void runCommand(std::string input);
        void takeFirstPlayerToken();
        void endOfRound();
        void calculatePlayerScoreChanged(Player* player, int row, int col);
        void printPlayerScores();

    private:
        int roundNumber;
        int turnNumber;
        int currentPlayerIndex;
        bool firstPlayerTokenTaken;
        TileBag* tileBag;
        Player** players;
        Player* currentPlayer;
        Factory** factories;
        std::vector<std::string> turnVector;

};

#endif