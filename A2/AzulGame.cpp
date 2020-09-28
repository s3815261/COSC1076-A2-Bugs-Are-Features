#include <iostream>
#include "AzulGame.h"

AzulGame::AzulGame(std::string player1Name, std::string player2Name)
{
    tileBag = new TileBag();
    player1 = new Player(player1Name);
    player2 = new Player(player2Name);
    factories = new Factory*[NUM_FACTORIES];
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        factories[i] = new Factory();
    }
}

AzulGame::~AzulGame()
{
    delete tileBag;
    delete player1;
    delete player2;
    for (int i = 0; i < NUM_FACTORIES; ++i) 
    {
        delete factories[i];
    }
    delete[] factories;
}

std::string AzulGame::getPlayer1Name()
{
    return player1->getName();
}

std::string AzulGame::getPlayer2Name()
{
    return player2->getName();
}

TileBag *AzulGame::getTileBag()
{
    return tileBag;
}

Factory** AzulGame::getFactories()
{
    return factories;
}

void AzulGame::setPlayer1Name(std::string player1Name)
{
    player1->setName(player1Name);
}

void AzulGame::setPlayer2Name(std::string player2Name)
{
    player2->setName(player2Name);
}

void AzulGame::addTurn(Turn turn)
{
    turn_vector.push_back(turn);
}

void AzulGame::populateFactories() 
{
    Tile* tile1 = new Tile(FIRST_PLAYER, 'F');

    Tile* tile2 = new Tile(RED, 'R');
    Tile* tile3 = new Tile(RED, 'Y');
    Tile* tile4 = new Tile(RED, 'Y');
    Tile* tile5 = new Tile(RED, 'U');

    Tile* tile6 = new Tile(RED, 'R');
    Tile* tile7 = new Tile(RED, 'B');
    Tile* tile8 = new Tile(RED, 'B');
    Tile* tile9 = new Tile(RED, 'B');

    Tile* tile10 = new Tile(RED, 'B');
    Tile* tile11 = new Tile(RED, 'L');
    Tile* tile12 = new Tile(RED, 'L');
    Tile* tile13 = new Tile(RED, 'L');

    Tile* tile14 = new Tile(RED, 'R');
    Tile* tile15 = new Tile(RED, 'R');
    Tile* tile16 = new Tile(RED, 'U');
    Tile* tile17 = new Tile(RED, 'U');

    Tile* tile18 = new Tile(RED, 'R');
    Tile* tile19 = new Tile(RED, 'Y');
    Tile* tile20 = new Tile(RED, 'B');
    Tile* tile21 = new Tile(RED, 'L');

    factories[0]->add(tile1);
    
    factories[1]->add(tile2);
    factories[1]->add(tile3);
    factories[1]->add(tile4);
    factories[1]->add(tile5);

    factories[2]->add(tile6);
    factories[2]->add(tile7);
    factories[2]->add(tile8);
    factories[2]->add(tile9);

    factories[3]->add(tile10);
    factories[3]->add(tile11);
    factories[3]->add(tile12);
    factories[3]->add(tile13);

    factories[4]->add(tile14);
    factories[4]->add(tile15);
    factories[4]->add(tile16);
    factories[4]->add(tile17);

    factories[5]->add(tile18);
    factories[5]->add(tile19);
    factories[5]->add(tile20);
    factories[5]->add(tile21);
}

void AzulGame::printPlayerNames()
{
    std::cout << "Player 1 name: " << player1->getName() << std::endl;
    std::cout << "Player 2 name: " << player2->getName() << std::endl;
}

void AzulGame::playGame()
{
    int maxTurns = 2;
    int turn = 0;
    bool player1Turn = true;
    std::cout << std::endl;
    std::cout << "=== Start Round ===" << std::endl;
    populateFactories();
    while (turn < maxTurns && !std::cin.eof())
    {
        std::string input = "";
        printBoard(player1Turn);
        if (turn == 0)
        {
            std::cout << std::endl;
            std::cout << "> ";
        }
        else
        {
            std::cout << "> ";
        }
        getline(std::cin, input);
        while (input.length() != 10 && std::cin && !std::cin.eof())
        {
            std::cout << "> ";
            getline(std::cin, input);
        }
        if (!std::cin.eof())
        {
            runCommand(input, player1Turn);            
        }
        ++turn;
        if (player1Turn == true)
        {
            player1Turn = false;
        }
        else 
        {
            player1Turn = true;
        }
        if (turn % 2 == 0 && !std::cin.eof())
        {
            std::cout << "=== END OF ROUND ===" << std::endl;
            std::cout << std::endl;
            std::cout << "=== Start Round ===" << std::endl;
            std::cout << std::endl;
        }
    }
}

void AzulGame::printBoard(bool player1Turn) 
{
    std::cout << "TURN FOR PLAYER: ";
    if (player1Turn)
    {
        
        std::cout << getPlayer1Name() << std::endl;
        printFactories();
        std::cout << std::endl;
        std::cout << "Mosaic for " << getPlayer1Name() << ":" << std::endl;
        player1->getPlayerBoard()->printPlayerBoard();
        std::cout << "broken: " << std::endl;
    }
    else 
    {
        std::cout << getPlayer2Name() << std::endl;
        printFactories();
        std::cout << std::endl;
        std::cout << "Mosaic for " << getPlayer2Name() << ":" << std::endl;
        player2->getPlayerBoard()->printPlayerBoard();
        std::cout << "broken: " << std::endl;
    }
}

void AzulGame::printFactories()
{
    std::cout << "Factories:" << std::endl;
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        std::cout << i << ": ";
        for (int j = 0; j < factories[i]->size(); ++j)
        {
            std::cout << factories[i]->get(j)->getTile() << ' ';
        }
        std::cout << std::endl;
    }
}

void AzulGame::runCommand(std::string input, bool player1Turn)
{
    std::string command = input.substr(0, 4);
    if (command == "turn") // turn 2 R 3
    {
        int factoryNumber = std::stoi(input.substr(5, 6));
        char tile = input[7];
        int storageRow = std::stoi(input.substr(9, 10));
        // std::cout << "Command: " << command << std::endl;
        // std::cout << "Factory Number: " << factoryNumber << std::endl;
        // std::cout << "Tile: " << tile << std::endl;
        // std::cout << "Storage Row: " << storageRow << std::endl;
        if (player1Turn)
        {
            PlayerBoard *playerBoard = player1->getPlayerBoard();
            Factory* factory = factories[factoryNumber];
            Tile** commonTiles = factory->popSameTile(*factory, tile);
            // std::cout << factory->sameTileLength << std::endl;
            for (int i = 0; i < factory->sameTileLength; ++i)
            {
                playerBoard->addTiletoRow(commonTiles[i], storageRow);
                // std::cout << "Tile Added" << std::endl;
            }
            for (int i = 0; i < factory->size(); ++i)
            {
                factories[0]->add(factory->get(i));
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
        else 
        {
            PlayerBoard *playerBoard = player2->getPlayerBoard();
            Factory* factory = factories[factoryNumber];
            Tile** commonTiles = factory->popSameTile(*factory, tile);
            // std::cout << factory->sameTileLength << std::endl;
            for (int i = 0; i < factory->sameTileLength; ++i)
            {
                playerBoard->addTiletoRow(commonTiles[i], storageRow);
                // std::cout << "Tile Added" << std::endl;
            }
            for (int i = 0; i < factory->size(); ++i)
            {
                factories[0]->add(factory->get(i));
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
}