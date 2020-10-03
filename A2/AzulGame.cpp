#include <iostream>
#include <fstream>
#include <sstream>

#include "AzulGame.h"

AzulGame::AzulGame() :
    roundNumber(0),
    turnNumber(0)
{
    tileBag = new TileBag();
    players = new Player *[NUM_PLAYERS];
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        players[i] = new Player("Player " + std::to_string(i + 1));
    }
    factories = new Factory *[NUM_FACTORIES];
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        factories[i] = new Factory();
    }
    broken = new Factory();
}

AzulGame::~AzulGame()
{
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
    delete broken;
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

Factory* AzulGame::getBroken()
{
    return broken;
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
    Tile *First_Player_Token = new Tile('F');
    int numTiles = 0;
    factories[0]->add(First_Player_Token);
    ++numTiles;

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
    bool player1Turn = true;
    while (roundNumber != maxRounds && !std::cin.eof())
    {
        std::cout << std::endl;
        std::cout << "=== Start Round ===" << std::endl;
        if (roundNumber != 0)
        {
            populateFactories();
        }
        while (!factoriesIsEmpty() && !std::cin.eof())
        {
            std::string input = "";
            printPlayer1Board(player1Turn);
            if (turnNumber == 0)
            {
                takeFirstPlayerToken(player1Turn);
                std::cout << std::endl;
                std::cout << "> ";
            }
            else
            {
                std::cout << "> ";
            }
            //getline(std::cin, input);
            while (input.length() != 10 && !std::cin.eof())
            {
                // std::cout << "> ";
                getline(std::cin, input);
            }
            if (!std::cin.eof())
            {
                runCommand(input, player1Turn);
            }
            ++turnNumber;
            if (player1Turn == true)
            {
                player1Turn = false;
            }
            else
            {
                player1Turn = true;
            }
        }
        if (!std::cin.eof())
        {
            std::cout << "=== END OF ROUND ===" << std::endl;
            std::cout << std::endl;
            endOfRound();
            turnNumber = 0;
            ++roundNumber;
        }
    }
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
    bool player1Turn = true;
    //
    for (int turn = 0; turn < turnVectorSize; ++turn)
    {
        //define the vector string, run command with string plus player number
        if (turn % 2 == 0)
        {
            player1Turn = true;
        }
        else
        {
            player1Turn = false;
        }
        if (turnNumber == 0) 
        {
            takeFirstPlayerToken(player1Turn);
        }
        runCommand(turnVector[turn], player1Turn);
        ++turnNumber;
        if (factoriesIsEmpty())
        {
            endOfRound();
            turnNumber = 0;
            ++roundNumber;
        }
    }
}

void AzulGame::printPlayer1Board(bool player1Turn)
{
    std::cout << "TURN FOR PLAYER: ";
    if (player1Turn)
    {
        std::cout << players[PLAYER1_INDEX]->getName() << std::endl;
        printFactories();
        std::cout << std::endl;
        std::cout << "Mosaic for " << players[PLAYER1_INDEX]->getName() << ":" << std::endl;
        players[PLAYER1_INDEX]->getPlayerBoard()->printPlayerBoard();
        std::cout << "broken: ";
        broken->printFactory();
        std::cout << std::endl;
    }
    else
    {
        std::cout << players[PLAYER2_INDEX]->getName() << std::endl;
        printFactories();
        std::cout << std::endl;
        std::cout << "Mosaic for " << players[PLAYER2_INDEX]->getName() << ":" << std::endl;
        players[PLAYER2_INDEX]->getPlayerBoard()->printPlayerBoard();
        std::cout << "broken: ";
        broken->printFactory();
        std::cout << std::endl;
    }
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

bool AzulGame::checkCommandIsValid(std::string input)
{
    return false;
}

void AzulGame::runCommand(std::string input, bool player1Turn)
{
    std::string command = input.substr(0, 4);
    if (command == "turn")
    {
        Player *player = nullptr;
        int factoryNumber = std::stoi(input.substr(5, 6));
        char tile = input[7];
        int storageRow = std::stoi(input.substr(9, 10));
        // std::cout << "Command: " << command << std::endl;
        // std::cout << "Factory Number: " << factoryNumber << std::endl;
        // std::cout << "Tile: " << tile << std::endl;
        // std::cout << "Storage Row: " << storageRow << std::endl;
        if (player1Turn)
        {
            player = players[PLAYER1_INDEX];
        }
        else
        {
            player = players[PLAYER2_INDEX];
        }
        if (player != nullptr)
        {
            PlayerBoard* playerBoard = player->getPlayerBoard();
            Factory* factory = factories[factoryNumber];
            Tile** commonTiles = factory->popSameTile(*factory, tile);
            // std::cout << factory->sameTileLength << std::endl;
            for (int i = 0; i < factory->getSameTileLength(); ++i)
            {
                playerBoard->addTiletoRow(commonTiles[i], storageRow);
                // std::cout << "Tile Added" << std::endl;
            }
            for (int i = 0; i < factory->size(); ++i)
            {
                if (factory->get(i) != nullptr)
                {
                    factories[0]->add(factory->get(i));
                }
            }
            factory->clearAll();
            std::cout << "Turn successful." << std::endl;
            std::cout << std::endl;
            // for (int i = 0;  i < 20; ++i)
            // {
            //     if (commonTiles[i] != nullptr)
            //     {
            //         std::cout << commonTiles[i]->getTile() << std::endl;
            //     }
            // }
        }
    }
    else if (command == "save")
    {
        //Get save file name
        std::cout << std::endl;
        std::cout << "Enter the name you wish to save the file as" << std::endl;
        std::cout << "> ";
        std::string filename;
        std::cin >> filename;

        //Create save file
        std::ofstream saveFile(filename);
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
                for( std::vector<std::string>::iterator it = turn_vector.begin() ; it != turn_vector.end() ; ++it )
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
            saveFile.close();
        }
    }
}

void AzulGame::takeFirstPlayerToken(bool player1Turn)
{
    
}

void AzulGame::endOfRound() 
{

}

void AzulGame::calculateScore(bool player1Turn)
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
