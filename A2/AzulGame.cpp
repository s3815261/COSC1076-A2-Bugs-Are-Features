#include <iostream>
#include <fstream>
#include <sstream>

#include "AzulGame.h"

AzulGame::AzulGame() :
    roundNumber(0),
    turnNumber(0),
    currentPlayerIndex(PLAYER1_INDEX)
{
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

void AzulGame::addTurn(std::string turn)
{
    turnVector.push_back(turn);
}

std::vector<std::string> AzulGame::getTurns()
{
    return turnVector;
}

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
    Tile *firstPlayerToken = new Tile('F');
    int numTiles = 0;
    factories[0]->add(firstPlayerToken);
    ++numTiles;
    firstPlayerToken = nullptr;

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

bool AzulGame::factoriesIsEmpty()
{
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

void AzulGame::printPlayerNames()
{
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        std::cout << "Player " << i + 1 << " name: " << players[i]->getName() << std::endl;
    }
}

void AzulGame::newGame()
{
    tileBag->initaliseTileBag();
    populateFactories();
}

void AzulGame::playGame()
{
    int maxRounds = 5;
    while (roundNumber != maxRounds && !std::cin.eof())
    {
        bool firstPlayerTokenTaken = false;
        std::cout << std::endl;
        std::cout << "=== Start Round ===" << std::endl;
        if (roundNumber != 0)
        {
            populateFactories();
        }
        while (!factoriesIsEmpty() && !std::cin.eof())
        {
            bool inputValid = false;
            std::string input = "";
            printPlayerGameBoard();
            if (turnNumber == 0)
            {
                if (!firstPlayerTokenTaken)
                {
                    takeFirstPlayerToken();
                    firstPlayerTokenTaken = true;
                }
                std::cout << std::endl;
                std::cout << "> ";
            }
            else
            {
                std::cout << "> ";
            }
            while (!inputValid && !std::cin.eof())
            {
                getline(std::cin, input);
                if (!std::cin.eof())
                {
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
                runCommand(input);
            }
            if (input.substr(0, 4) != "save") 
            {
                ++turnNumber;
                nextPlayerTurn();
            }
        }
        if (!std::cin.eof())
        {
            std::cout << "=== END OF ROUND ===" << std::endl;
            std::cout << std::endl;
            endOfRound();
            firstPlayerTokenTaken = false;
            turnNumber = 0;
            ++roundNumber;
        }
    }
}

void AzulGame::nextPlayerTurn()
{
    ++currentPlayerIndex; 
    if (currentPlayerIndex == NUM_PLAYERS)
    {
        currentPlayerIndex = 0;
    }
    currentPlayer = players[currentPlayerIndex];
}

// assume tileBag has been loaded in?
void AzulGame::loadGame()
{

    //{"turn 0 y 4", "turn 2 b 3"....}
    //loop through the vector of turns/strings and make moves
    //start from the last poistion that was read in (depending on if you read in moves of if its a new game)
    // int turn_index = turn_vector.size();
    populateFactories();
    int turnVectorSize = turnVector.size();
    bool firstPlayerTokenTaken = false;

    for (int turn = 0; turn < turnVectorSize; ++turn)
    {
        //define the vector string, run command with string plus player number
        if (turnNumber == 0) 
        {
            if (!firstPlayerTokenTaken)
            {
                takeFirstPlayerToken();
                firstPlayerTokenTaken = true;
            }
        }
        bool isValid = isCommandValid(turnVector[turn]);
        if (isValid)
        {
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
        else
        {
            std::cout << "Invalid Input" << std::endl;
        }
    }
}

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

bool AzulGame::isCommandValid(std::string input)
{
    bool isValid = true;
    std::string command = input.substr(0, 4);
    if (command == "turn" && input.length() == 10)
    {
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
        if (fns.fail() || ts.fail() || srs.fail())
        {
            isValid = false;
        }
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
        else if (!srs.fail())
        {
            if (storageRow < 1 || storageRow > 5)
            {
                isValid = false;
            }
        }
        if (isValid)
        {
            PlayerBoard* playerBoard = currentPlayer->getPlayerBoard();
            Tile* tile = playerBoard->getStorageRowTile(storageRow - 1); 
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

bool AzulGame::isValidTile(char tileChar)
{
    bool returnValue = false;
    if(tileChar == RED || tileChar == YELLOW || tileChar == DARK_BLUE || tileChar == LIGHT_BLUE || tileChar == BLACK)
    {
        returnValue = true;
    }
    return returnValue;
}

void AzulGame::runCommand(std::string input)
{
    std::string command = input.substr(0, 4);
    if (command == "turn")
    {
        int factoryNumber = std::stoi(input.substr(5, 6));
        char tile = input[7];
        int storageRow = std::stoi(input.substr(9, 10)) - 1;
        PlayerBoard* playerBoard = currentPlayer->getPlayerBoard();
        Factory* factory = factories[factoryNumber];
        Tile** commonTiles = factory->popSameTile(tile);
        Factory* broken = playerBoard->getBroken();
        Tile* storageRowTile = playerBoard->getStorageRowTile(storageRow);
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
            if(saveFile.is_open())
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
                for (std::vector<std::string>::iterator it = turn_vector.begin() ; it != turn_vector.end() ; ++it)
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

void AzulGame::takeFirstPlayerToken()
{
    Factory* centralFactory = factories[CENTRAL_FACTORY_INDEX];
    Factory* broken = currentPlayer->getPlayerBoard()->getBroken();
    Tile* firstPlayerTile = centralFactory->popFront();
    broken->add(firstPlayerTile);
    firstPlayerTile = nullptr;
}

void AzulGame::endOfRound() 
{
    for (int i = 0; i < NUM_PLAYERS; ++i) 
    {
        for (int row = 0; row < MAX_BOARD_ROWS; ++row) 
        {
            PlayerBoard* playerBoard = players[i]->getPlayerBoard();
            if (playerBoard->isStorageRowFull(row)) 
            {
                Tile* tile = playerBoard->popTileFromStorageRow(row); 
                playerBoard->addTiletoMosaic(tile, row);
                int row = 0;
                int col = 0;




                delete tile; 
                tile = nullptr;
                playerBoard->clearStorageRow(row);
            }
        }
    }
}

void AzulGame::calculateScore()
{
    // int score = 0;
    // int player1Score = 0;
    // int player2Score = 0;
    // int adjacentTiles = 0;
    // int floorline = 0;
    // int floorlineIndex = 0;

    // if (player1Turn == true)
    // {
    //     players[PLAYER1_INDEX]->getPlayerBoard();
    //   if (//tile is not adjacent to anything)
    //         {
    //         ++adjacentTiles;
    //         }
    //         else if (//tile is adjacent)
    //         {
    //             if (//tile has one adjacent tile left, right, up or down)
    //             {
    //             adjacentTiles += 2;
    //             }
    //             else if (//tile has two adjacent tiles left, right, up or down)
    //             {
    //             adjacentTiles += 3;
    //             }
    //             ++player2Score + adjacentTiles;
    //         }
    //     if (//end of round)
    //     {
    //         //for each tile in floorlineIndex
    //         //++floorlineIndex
    //         while (int i = 0; i < floorlineIndex; ++i)
    //             if (i < 2 && i > -1)
    //             {
    //                 ++floorline;
    //                 ++i;
    //             }
    //             else if (i > 1 && i < 5)
    //             {
    //                 floorline += 2;
    //                 ++i;
    //             }
    //             else if (i > 4 && i < 7)
    //             {
    //                 floorline += 3;
    //                 ++i;
    //             }
    //         player1Score - floorline;
    //     }
    //     player1Score = score;
    // }
    // else if (player1Turn == false)
    // {
    //     {
    //         players[PLAYER2_INDEX]->getPlayerBoard();
    //         if (//tile is not adjacent to anything)
    //         {
    //             ++adjacentTiles;
    //         }
    //         else if (//tile is adjacent)
    //         {
    //             if (//tile has one adjacent tile left, right, up or down)
    //             {
    //                 adjacentTiles += 2;
    //             }
    //             else if (//tile has two adjacent tiles left, right, up or down)
    //             {
    //                 adjacentTiles += 3;
    //             }
    //             ++player2Score + adjacentTiles;
    //         }
    //         if (//end of round)
    //         {
    //             //for each tile in floorlineIndex
    //             //++floorlineIndex
    //             while (int i = 0; i < floorlineIndex; ++i)
    //                 if (i < 2 && i > -1)
    //                 {
    //                     ++floorline;
    //                     ++i;
    //                 }
    //                 else if (i > 1 && i < 5)
    //                 {
    //                     floorline += 2;
    //                     ++i;
    //                 }
    //                 else if (i > 4 && i < 7)
    //                 {
    //                     floorline += 3;
    //                     ++i;
    //                 }
    //             player2Score - floorline;
    //         }
    //         player2Score = score;
    //     }

    //     return score;
    // }
}
