#include <iostream>
#include <fstream>
#include <sstream>

#include "AzulGame.h"

//Azul game constructor
AzulGame::AzulGame() : 
    roundNumber(0),
    turnNumber(0),
    currentPlayerIndex(PLAYER1_INDEX),
    firstPlayerTokenTaken(false)
{
    //Creates a new tile bag, player and factories
    tileBag = new TileBag();
    players = new Player *[NUM_PLAYERS];
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        players[i] = new Player("Player " + std::to_string(i + 1));
    }
    currentPlayer = players[currentPlayerIndex];
    factories = new Factory *[NUM_FACTORIES];
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        factories[i] = new Factory();
    }
}

//Destructor deletes players, factories and tilebag
AzulGame::~AzulGame()
{
    currentPlayer = nullptr;
    delete tileBag;
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        if (players[i] != nullptr)
        {
            delete players[i];
        }
    }
    delete[] players;
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        if (factories[i] != nullptr)
        {
            delete factories[i];
        }
    }
    delete[] factories;
}

//All getters that return the tile bag, players and factories
TileBag *AzulGame::getTileBag()
{
    return tileBag;
}

Player **AzulGame::getPlayers()
{
    return players;
}

Factory **AzulGame::getFactories()
{
    return factories;
}

std::vector<std::string> AzulGame::getTurns()
{
    return turnVector;
}

//Sets the player names
void AzulGame::setPlayerNames(std::string playerNameArray[])
{
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        players[i]->setName(playerNameArray[i]);
    }
}

//Intialises the new game
void AzulGame::newGame()
{
    //Creates and inital tile bag to start the game, populates the factories with tiles
    tileBag->initaliseTileBag();
    populateFactories();
}

//Loads in the turns, tilebag and factory loaded in main function of load game
void AzulGame::loadGame()
{
    //Loop through the vector of turns/strings and make moves
    populateFactories();
    int turnVectorSize = turnVector.size();

    for (int turn = 0; turn < turnVectorSize; ++turn)
    {
        //Checks if turn is valid, else stop loading
        bool isValid = isCommandValid(turnVector[turn]);
        if (isValid)
        {
            //Makes the turn if it is valid
            runCommand(turnVector[turn], true);
            ++turnNumber;
            nextPlayerTurn();
            if (factoriesIsEmpty())
            {
                endOfRound();
                firstPlayerTokenTaken = false;
                turnNumber = 0;
                ++roundNumber;
            }
        }
        //Errors and asks for an appropriate load game file if a turn is invalid
        else
        {
            std::cout << "Error with turn read in, Enter appropriate load game file" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

//Allows the game to be played
void AzulGame::playGame()
{
    //Sets the max number of rounds
    int maxRounds = 5;
    //Will player until round number = 5 or end of file
    while (roundNumber != maxRounds && !std::cin.eof())
    {
        std::cout << std::endl;
        std::cout << "=== Start Round ===" << std::endl;
        if (roundNumber != 0)
        {
            //Populates the factories
            populateFactories();
        }
        //While a round is in progress, factories not empty
        while (!factoriesIsEmpty() && !std::cin.eof())
        {
            bool inputValid = false;
            std::string input = "";
            printPlayerGameBoard();
            if (turnNumber == 0)
            {
                std::cout << std::endl;
                std::cout << "> ";
            }
            else
            {
                std::cout << "> ";
            }
            //Makes sure the input is valid
            while (!inputValid && !std::cin.eof())
            {
                //Reads in input
                getline(std::cin, input);
                if (!std::cin.eof() && input.length() != 0)
                {
                    //Checks if input is valid
                    inputValid = isCommandValid(input);
                    if (!inputValid)
                    {
                        std::cout << "Invalid Input" << std::endl;
                        std::cout << "> ";
                    }
                }
            }
            if (inputValid && !std::cin.eof())
            {
                //Runs a turn if it is valid
                runCommand(input, false);
            }
            if (input.length() != 0) {
                if (input.substr(0,4) != "save") {
                   //Goes to next players turn
                    ++turnNumber;
                    nextPlayerTurn(); 
                }
            }
        }
        if (!std::cin.eof())
        {
            //End of round handling
            endOfRound();
        }
    }
    if (!std::cin.eof())
    {
        //End of game handling
        std::cout << "=== GAME OVER ===" << std::endl;
        std::cout << std::endl;
        std::cout << "Final Score:" << std::endl;
        int winningPlayerIndex = 0;
        int highestScore = 0;
        for (int i = 0; i < NUM_PLAYERS; ++i)
        {
            if (players[i]->getScore() > highestScore)
            {
                highestScore = players[i]->getScore();
                winningPlayerIndex = i;
            }
        }
        printPlayerScores();
        std::cout << "Player " << players[winningPlayerIndex]->getName() << " wins!" << std::endl;
    }
}

//Initialises the factories for new game
void AzulGame::populateFactories()
{
    //Creates a new first player token tile
    Tile *firstPlayerToken = new Tile('F');
    int numTiles = 0;
    //Adds the F tile to the central factory
    factories[0]->add(firstPlayerToken);
    ++numTiles;
    firstPlayerToken = nullptr;

    //Places tiles in each factory until they are full
    int factoryIndex = 1;
    for (int tilesPlaced = numTiles; tilesPlaced < MAX_TILES + 1; ++tilesPlaced)
    {
        if (tilesPlaced % 4 != 0)
        {
            factories[factoryIndex]->add(tileBag->popFront());
        }
        else
        {
            factories[factoryIndex]->add(tileBag->popFront());
            ++factoryIndex;
        }
    }
}

//Checks if a command/turn is valid
bool AzulGame::isCommandValid(std::string input)
{
    bool isValid = true;
    std::string command = input.substr(0, 4);
    if (command == "turn" && input.length() == 10)
    {
        //Checks the value of each part of the turn using sub strings
        int factoryNumber;
        char tileChar;
        int storageRow;
        std::string factoryNumberString = input.substr(5, 6);
        std::string tileString = input.substr(7, 7);
        std::string storageRowString = input.substr(9, 10);
        std::istringstream fns(factoryNumberString);
        fns >> factoryNumber;
        std::istringstream ts(tileString);
        ts >> tileChar;
        std::istringstream srs(storageRowString);
        srs >> storageRow;
        //If any of them fail, isValid is false
        if (fns.fail() || ts.fail() || srs.fail())
        {
            isValid = false;
        }
        //If factory number is out of bounds it is not a valid turn
        if (!fns.fail())
        {
            if (factoryNumber < 0 || factoryNumber > 5)
            {
                isValid = false;
            }
        }
        //If the tile is not a valid tile
        if (!ts.fail())
        {
            if (!isValidTile(tileChar))
            {
                isValid = false;
            }
        }
        //If storage row is out of bounds it is not a valid turn
        if (!srs.fail())
        {
            if (storageRow < 1 || storageRow > 5)
            {
                isValid = false;
            }
        }
        if (isValid)
        { 
            if (factories[factoryNumber]->size() == 0)
            {
                isValid = false;
            }
            bool tileFound = false;
            for (int i = 0; i < factories[factoryNumber]->size(); ++i) 
            {
                if (!tileFound)
                {
                    if (factories[factoryNumber]->get(i) != nullptr)
                    {
                        if (factories[factoryNumber]->get(i)->getTile() == tileChar) 
                        {
                            tileFound = true; 
                        }
                    }
                }
            }
            isValid = tileFound;
        }
    }
    else if (input.length() == 0)
    {
        isValid = true;
    }
    else if (command == "save" && input.length() > 4)
    {
        std::string fileName = input.substr(5, input.length());
        if (fileName.at(fileName.length() - 1) == ' ')
        {
            isValid = false;
        }
    }
    else
    {
        isValid = false;
    }
    return isValid;
}

//Checks if the tile is valid
bool AzulGame::isValidTile(char tileChar)
{
    //Makes sure a tile is only red, yellow, blue, light blue or black
    bool returnValue = false;
    if (tileChar == RED || tileChar == YELLOW || tileChar == DARK_BLUE || tileChar == LIGHT_BLUE || tileChar == BLACK)
    {
        returnValue = true;
    }
    return returnValue;
}

//Runs the turn or save command
void AzulGame::runCommand(std::string input, bool loadingGame)
{
    std::string command = input.substr(0, 4);
    if (command == "turn")
    {
        int factoryNumber = std::stoi(input.substr(5, 6));
        char tile = input[7];
        int storageRow = std::stoi(input.substr(9, 10)) - 1;
        PlayerBoard *playerBoard = currentPlayer->getPlayerBoard();
        Factory *factory = factories[factoryNumber];
        Tile **commonTiles = factory->popSameTile(tile);
        Factory *broken = playerBoard->getBroken();
        Tile *storageRowTile = playerBoard->getStorageRowTile(storageRow);
        if (factoryNumber == 0)
        {
            if (firstPlayerTokenTaken == false)
            {
                takeFirstPlayerToken();
                firstPlayerTokenTaken = true;
            }
        }
        //Makes sure that the tiles can be placed in broken if they cannot place anywhere. 
        for (int i = 0; i < factory->getSameTileLength(); ++i)
        {
            if (!playerBoard->isStorageRowFull(storageRow))
            {
                if (storageRowTile != nullptr) 
                {
                    if (storageRowTile->getTile() == tile) 
                    {
                        playerBoard->addTileToStorageRow(commonTiles[i], storageRow);
                        delete commonTiles[i];
                        commonTiles[i] = nullptr;
                    }
                    else
                    {
                        broken->add(commonTiles[i]);
                        commonTiles[i] = nullptr;
                    }
                }
                else 
                {
                    playerBoard->addTileToStorageRow(commonTiles[i], storageRow);
                    delete commonTiles[i];
                    commonTiles[i] = nullptr;
                }
            }
            else 
            {
                broken->add(commonTiles[i]);
                commonTiles[i] = nullptr;
            }
        }
        delete storageRowTile;
        storageRowTile = nullptr;
        //Adds the remaining tiles from the factory that was just taken from to central
        if (factoryNumber != 0)
        {
            for (int i = 0; i < factory->size(); ++i)
            {
                if (factory->get(i) != nullptr)
                {
                    factories[0]->add(factory->get(i));
                }
            }
            factory->clearAll();
        }
        //Delete the tiles taken from the factories as they are now saved on the board
        for (int i = 0; i < factory->getSameTileLength(); ++i)
        {
            if (commonTiles[i] != nullptr)
            {
                delete commonTiles[i];
                commonTiles[i] = nullptr;
            }
        }
        delete[] commonTiles;
        //Makes it so that it will not spam when loading the game
        if (!loadingGame)
        {
            std::cout << "Turn successful." << std::endl;
            std::cout << std::endl; 
        }
        addTurn(input);
    }
    else if (command == "save")
    {
        //Get save file name
        std::string fileName = input.substr(5, input.length());

        //Create save file
        std::ofstream saveFile(fileName);
        //Saving contents to the file
        if (!saveFile.fail())
        {
            if (saveFile.is_open())
            {
                //Get the variables to save.....
                std::string tileBag = getTileBag()->saveTileBag();
                std::string player1 = getPlayers()[PLAYER1_INDEX]->getName();
                std::string player2 = getPlayers()[PLAYER2_INDEX]->getName();
                std::vector<std::string> turn_vector = getTurns();
                //Save the tilebag
                saveFile << tileBag << std::endl;
                //Save the name of player one
                saveFile << player1 << std::endl;
                //Save the name of player two
                saveFile << player2 << std::endl;
                //Go through the turns and save each of them to the file.
                for (std::vector<std::string>::iterator it = turn_vector.begin(); it != turn_vector.end(); ++it)
                {
                    std::string turn = "";
                    turn = *it;
                    saveFile << turn << std::endl;
                }
            }
        }
        //Close the file, should have the saved contents
        if (saveFile.is_open())
        {
            std::cout << std::endl;
            std::cout << "Game Successfully saved to '" << fileName << "'" << std::endl;
            std::cout << std::endl;
            saveFile.close();
        }
    }
}

//Adds turns
void AzulGame::addTurn(std::string turn)
{
    turnVector.push_back(turn);
}

//Gives the first player token to which player's turn it is
void AzulGame::takeFirstPlayerToken()
{
    Factory *centralFactory = factories[CENTRAL_FACTORY_INDEX];
    Factory *broken = currentPlayer->getPlayerBoard()->getBroken();
    Tile *firstPlayerTile = centralFactory->popFront();
    broken->add(firstPlayerTile);
    firstPlayerTile = nullptr;
}

//Moves to the next players turn
void AzulGame::nextPlayerTurn()
{
    ++currentPlayerIndex;
    if (currentPlayerIndex == NUM_PLAYERS)
    {
        currentPlayerIndex = 0;
    }
    currentPlayer = players[currentPlayerIndex];
}

//Boolean to check if the factories are empty
bool AzulGame::factoriesIsEmpty()
{
    //Is true unless there is a tile in a factory
    bool isEmpty = true;
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        if (factories[i]->size() != 0)
        {
            isEmpty = false;
        }
    }
    return isEmpty;
}

//Runs all commands for end of round including adding tiles to mosaic, clearing the rows.
void AzulGame::endOfRound()
{
    std::cout << "=== END OF ROUND ===" << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        for (int row = 0; row < MAX_BOARD_ROWS; ++row)
        {
            PlayerBoard *playerBoard = players[i]->getPlayerBoard();
            if (playerBoard->isStorageRowFull(row))
            {
                Tile *tile = playerBoard->popTileFromStorageRow(row);
                playerBoard->addTileToMosaic(tile, row);
                char tileChar = tile->getTile();
                int col = playerBoard->getTileColumnOnMosaic(tileChar, row);
                delete tile; 
                tile = nullptr;
                calculatePlayerScoreChange(players[i], row, col);
                playerBoard->clearStorageRow(row);
                playerBoard->clearBroken();
            }
        }
    }
    std::cout << "Current Scores:" << std::endl;
    printPlayerScores();
    firstPlayerTokenTaken = false;
    turnNumber = 0;
    ++roundNumber;
}

//Calculates the player score if the mosaic has been changed
void AzulGame::calculatePlayerScoreChange(Player* player, int row, int col)
{
    int negativePoint[MAX_BROKEN] = { 1, 1, 2, 2, 2, 3, 3 };
    int additionToScore = 0;
    int subtractionToScore = 0;
    additionToScore += player->getPlayerBoard()->countAdjacentTilesVertical(row, col) + 1;
    additionToScore += player->getPlayerBoard()->countAdjacentTilesHorizontal(row, col) + 1;
    Factory* broken = player->getPlayerBoard()->getBroken();
    for (int i = 0; i < MAX_BROKEN && i < broken->size(); ++i) 
    {
        if (broken->get(i) != nullptr)
        {
            subtractionToScore += negativePoint[i]; 
        }
    }
    int playerScore = player->getScore(); 
    if (playerScore + additionToScore - subtractionToScore >= 0) 
    {
        int newPlayerScore = playerScore + additionToScore - subtractionToScore;
        player->setScore(newPlayerScore);
    }
    else 
    {
        player->setScore(0);
    }
}

//Prints the factories for each turn
void AzulGame::printFactories()
{
    std::cout << "Factories:" << std::endl;
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        std::cout << i << ": ";
        factories[i]->printFactory();
        std::cout << std::endl;
    }
}

//Prints the playerboard so people can see what moves to make
void AzulGame::printPlayerGameBoard()
{
    std::cout << "TURN FOR PLAYER: ";
    std::cout << currentPlayer->getName() << std::endl;
    printFactories();
    std::cout << std::endl;
    currentPlayer->printBoard();
}

//Prints the player names
void AzulGame::printPlayerNames()
{
    //Prints i number of player names
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        std::cout << "Player " << i + 1 << " name: " << players[i]->getName() << std::endl;
    }
}

//Prints the player scores
void AzulGame::printPlayerScores()
{
    for (int i = 0; i < NUM_PLAYERS; ++i) {
        std::cout<< "Player " << players[i]->getName() << ": " << players[i]->getScore() << std::endl;
    }
}
