#include <iostream>
#include <fstream>
#include <sstream>

#include "AzulGame.h"

//Azul game constructor
AzulGame::AzulGame() : roundNumber(0),
                       turnNumber(0),
                       currentPlayerIndex(PLAYER1_INDEX)
{
    //creates a new tile bag, player and factories
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

//deconstructor deletes players, factories and tilebag
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

//all getters that return the tile bag, players and factories
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

//adds and gets turns
void AzulGame::addTurn(std::string turn)
{
    turnVector.push_back(turn);
}

std::vector<std::string> AzulGame::getTurns()
{
    return turnVector;
}

//sets the player name
void AzulGame::setPlayerNames(std::string playerNameArray[])
{
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        players[i]->setName(playerNameArray[i]);
    }
}

// initialise factories for new game
void AzulGame::populateFactories()
{
    //creates a new first player token tile
    Tile *firstPlayerToken = new Tile('F');
    int numTiles = 0;
    //adds the F tile to the central factory
    factories[0]->add(firstPlayerToken);
    ++numTiles;
    firstPlayerToken = nullptr;

    //places tiles in each factory until they are full
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

//boolean to check if the factories are empty
bool AzulGame::factoriesIsEmpty()
{
    //is true unless there is a tile in a factory
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

//prints the player names
void AzulGame::printPlayerNames()
{
    //prints i number of player names
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        std::cout << "Player " << i + 1 << " name: " << players[i]->getName() << std::endl;
    }
}

//intialise the new game
void AzulGame::newGame()
{
    //creates and inital tile bag to start the game, populates the factories with tiles
    tileBag->initaliseTileBag();
    populateFactories();
}

//allows the game to be played
void AzulGame::playGame()
{
    //sets the max number of rounds
    int maxRounds = 5;
    //will player until round number = 5 or end of file
    while (roundNumber != maxRounds && !std::cin.eof())
    {
        std::cout << std::endl;
        std::cout << "=== Start Round ===" << std::endl;
        if (roundNumber != 0)
        {
            //populates the factories
            populateFactories();
        }
        //while a round is in progress, factories not empty
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
            while (!inputValid && !std::cin.eof())
            {
                //reads in input
                getline(std::cin, input);
                if (!std::cin.eof() && input.length() != 0)
                {
                    //checks if input is valid
                    inputValid = isCommandValid(input);
                    if (!inputValid)
                    {
                        std::cout << "Invalid Input" << std::endl;
                        std::cout << "> ";
                    }
                }
            }
            if (!std::cin.eof())
            {
                //runs a turn if it is valid
                runCommand(input);
            }
            if (input.length() != 0) {
                if (input.substr(0,4) != "save") {
                   //goes to next players turn
                ++turnNumber;
                nextPlayerTurn(); 
                }
            }
        }
        if (!std::cin.eof())
        {
            //end of round
            std::cout << "=== END OF ROUND ===" << std::endl;
            std::cout << std::endl;
            endOfRound();
            firstPlayerTokenTaken = false;
            turnNumber = 0;
            ++roundNumber;
        }
    }
}
//moves to the next players turn
void AzulGame::nextPlayerTurn()
{
    ++currentPlayerIndex;
    if (currentPlayerIndex == NUM_PLAYERS)
    {
        currentPlayerIndex = 0;
    }
    currentPlayer = players[currentPlayerIndex];
}

//loads in the turns, tilebag and factory loaded in main function of load game
void AzulGame::loadGame()
{

    //loop through the vector of turns/strings and make moves
    populateFactories();
    int turnVectorSize = turnVector.size();

    for (int turn = 0; turn < turnVectorSize; ++turn)
    {
        //checks if turn is valid, else stop loading
        bool isValid = isCommandValid(turnVector[turn]);
        if (isValid)
        {
            //makes the turn if it is valid
            runCommand(turnVector[turn]);
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
        //errors and asks for an appropriate load game file if a turn is invalid
        else
        {
            std::cout << "Error with turn read in, Enter appropriate load game file" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

//prints the playerboard so people can see what moves to make
void AzulGame::printPlayerGameBoard()
{
    std::cout << "TURN FOR PLAYER: ";
    std::cout << currentPlayer->getName() << std::endl;
    printFactories();
    std::cout << std::endl;
    std::cout << "Mosaic for " << currentPlayer->getName() << ":" << std::endl;
    currentPlayer->getPlayerBoard()->printPlayerBoard();
    std::cout << "broken: ";
    currentPlayer->getPlayerBoard()->getBroken()->printFactory();
    std::cout << std::endl;
}

//prints the factories for each turn
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

//checks if a command/turn is valid
bool AzulGame::isCommandValid(std::string input)
{
    bool isValid = true;
    std::string command = input.substr(0, 4);
    if (command == "turn" && input.length() == 10)
    {
        //checks the value of each part of the turn using sub strings
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
        //if any of them fail isValid is false
        if (fns.fail() || ts.fail() || srs.fail())
        {
            isValid = false;
        }
        //if factory number is out of bounds it is not a valid turn
        else if (!fns.fail())
        {
            if (factoryNumber < 0 || factoryNumber > 5)
            {
                isValid = false;
            }
        }
        else if (!ts.fail())
        {
            if (!isValidTile(tileChar))
            {
                isValid = false;
            }
        }
        //if storage row is out of bounds it is not a valid turn
        else if (!srs.fail())
        {
            if (storageRow < 1 || storageRow > 5)
            {
                isValid = false;
            }
        }
        if (isValid)
        {
            PlayerBoard *playerBoard = currentPlayer->getPlayerBoard();
            Tile *tile = playerBoard->getStorageRowTile(storageRow - 1);
            if (!playerBoard->isStorageRowFull(storageRow - 1))
            {
                if (tile != nullptr)
                {
                    if (tile->getTile() != tileChar)
                    {
                        isValid = false;
                    }
                }
            }
            delete tile;
            tile = nullptr;
            if (factories[factoryNumber]->size() == 0)
            {
                isValid = false;
            }
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

//checks if the tile is valid
bool AzulGame::isValidTile(char tileChar)
{
    //makes sure a tile is only red, yellow, blue, light blue or black
    bool returnValue = false;
    if (tileChar == RED || tileChar == YELLOW || tileChar == DARK_BLUE || tileChar == LIGHT_BLUE || tileChar == BLACK)
    {
        returnValue = true;
    }
    return returnValue;
}

//runs/makes the turn/command to select tiles from factories and move them to the playerboard
void AzulGame::runCommand(std::string input)
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
        for (int i = 0; i < factory->getSameTileLength(); ++i)
        {
            if (!playerBoard->isStorageRowFull(storageRow))
            {
                if (storageRowTile != nullptr)
                {
                    if (storageRowTile->getTile() == tile)
                    {
                        playerBoard->addTiletoRow(commonTiles[i], storageRow);
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
                    playerBoard->addTiletoRow(commonTiles[i], storageRow);
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
        for (int i = 0; i < factory->getSameTileLength(); ++i)
        {
            if (commonTiles[i] != nullptr)
            {
                delete commonTiles[i];
                commonTiles[i] = nullptr;
            }
        }
        delete[] commonTiles;
        std::cout << "Turn successful." << std::endl;
        std::cout << std::endl;
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

//keeps track of who has the first player token
void AzulGame::takeFirstPlayerToken()
{
    Factory *centralFactory = factories[CENTRAL_FACTORY_INDEX];
    Factory *broken = currentPlayer->getPlayerBoard()->getBroken();
    Tile *firstPlayerTile = centralFactory->popFront();
    broken->add(firstPlayerTile);
    firstPlayerTile = nullptr;
}

//runs all commands for end of round including adding tiles to mosaic, clearing the rows.
void AzulGame::endOfRound()
{
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        for (int row = 0; row < MAX_BOARD_ROWS; ++row)
        {
            PlayerBoard *playerBoard = players[i]->getPlayerBoard();
            if (playerBoard->isStorageRowFull(row))
            {
                Tile *tile = playerBoard->popTileFromStorageRow(row);
                playerBoard->addTiletoMosaic(tile, row);
                char tileChar = tile->getTile();
                int col = playerBoard->getTileColumn(tileChar, row);
                delete tile; 
                tile = nullptr;
                calculatePlayerScoreChanged(players[i], row, col);
                playerBoard->clearStorageRow(row);
                playerBoard->clearBroken();
            }
        }
    }
}

void AzulGame::calculatePlayerScoreChanged(Player* player, int row, int col)
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
