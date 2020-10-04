#include <iostream>
#include <fstream>
#include <sstream>

#include "AzulGame.h"
#include "Player.h"
#include "TileBag.h"

void game(int argc, char **argv);
void mainMenu();
void displayPrimaryMenu(bool primaryMenu);
void newGame();
void loadGame(std::string fileName, bool testingMode);
void credits();
void eofQuit(bool eof);

#define NEWGAME 1
#define LOADGAME 2
#define CREDITS 3
#define EXITPROGRAM 4

//Main method
int main(int argc, char **argv)
{
    game(argc, argv);

    return EXIT_SUCCESS;
}

//Game method to handle the main menu or testing mode
void game(int argc, char **argv)
{
    if (argc == 1)
    {
        mainMenu();
    }
    else if (argc == 3)
    {
        std::string command(argv[1]);
        if (command == "-t")
        {
            std::string fileName(argv[2]);
            loadGame(fileName, true);
        }
        else
        {
            std::cout << "Invalid Command" << std::endl;   
        }
    }
}

//Main menu
void mainMenu()
{
    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "-------------------" << std::endl;
    displayPrimaryMenu(true);
    int option = 0;
    std::string input = "";
    // Loops continuously until it receives an eof command or a quit command option
    while (option != 4 && !std::cin.eof())
    {
        if (option != 0)
        {
            displayPrimaryMenu(false);
        }
        option = -1;

        bool validInput = false;

        while (!validInput && !std::cin.eof())
        {
            std::cout << "> ";
            getline(std::cin, input);
            std::istringstream stringStream(input);
            stringStream >> option;
            if (stringStream.fail() && !std::cin.eof())
            {
                std::cout << "Invalid Input" << std::endl;
            }
            else if (!(option >= 1 && option <= 4) && !std::cin.eof())
            {
                std::cout << "Invalid Input" << std::endl;
            }
            else
            {
                validInput = true;
            }
        }

        if (validInput && !std::cin.eof())
        {
            // Handles the selection of the menu options
            if (option == NEWGAME)
            {
                newGame();
            }
            else if (option == LOADGAME)
            {
                std::cout << std::endl;
                std::cout << "Enter the filename from which to load a game" << std::endl;
                std::cout << "> ";
                std::string filename;
                std::cin >> filename;
                loadGame(filename, false);
            }
            else if (option == CREDITS)
            {
                credits();
            }
            else if (option == EXITPROGRAM)
            {
                eofQuit(false);
            }
        }
    }
    if (std::cin.eof())
    {
        eofQuit(true);
    }
}

//Either displays the primary menu or the secondary menu
void displayPrimaryMenu(bool primaryMenu)
{
    if (primaryMenu)
    {
        std::cout << std::endl;
        std::cout << "Menu" << std::endl;
        std::cout << "----" << std::endl;
        std::cout << "1. New Game" << std::endl;
        std::cout << "2. Load Game" << std::endl;
        std::cout << "3. Credits (Show student information)" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << std::endl;
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Menu" << std::endl;
        std::cout << "----" << std::endl;
        std::cout << "1. New Game" << std::endl;
        std::cout << "2. Load Game" << std::endl;
        std::cout << "3. Show student information" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << std::endl;
    }
}

//Handles creating a new game and playing it
void newGame()
{
    std::string playerNames[NUM_PLAYERS];
    std::cout << std::endl;
    std::cout << "Starting a New Game" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter a name for player 1" << std::endl;
    std::string player1Name;
    std::cout << "> ";
    // No ignore input error due to reading an integer first which gives a "\n" symbol at the end before reading a char or string
    getline(std::cin, playerNames[PLAYER1_INDEX]);
    std::cout << std::endl;
    std::cout << "Enter a name for player 2" << std::endl;
    std::string player2Name;
    std::cout << "> ";
    getline(std::cin, playerNames[PLAYER2_INDEX]);
    std::cout << std::endl;
    AzulGame *ag = new AzulGame();
    
    ag->setPlayerNames(playerNames);
    //initalises the game
    if(playerNames[PLAYER1_INDEX].length() == 0 || playerNames[PLAYER2_INDEX].length() == 0) 
    {
        std::cout << "Name was empty, try again" << std::endl;
        newGame();
    } 
    else 
    {
        std::cout << "Let's Play!" << std::endl;
        ag->newGame();
        //plays the game with input
        ag->playGame();
    }
    delete ag;
}

//Handles loading a new game from save file. It also handles the printing for the testing mode
void loadGame(std::string fileName, bool testingMode)
{
    std::ifstream inputFile(fileName);
    //Check if the file has been successfully opened
    if (!inputFile.fail())
    {
        if (inputFile.is_open())
        {
            AzulGame *ag = new AzulGame();
            std::string playerNames[NUM_PLAYERS];
            int line_count = 0;
            while (!inputFile.eof())
            {
                std::string line;
                getline(inputFile, line);
                //For each character, tileBag.addBack(char)
                if (line_count == 0)
                {
                    int line_size = line.size();
                    for (int i = 0; i < line_size; ++i)
                    {
                        if (ag->isValidTile(line[i]))
                        {
                            Tile *new_tile = new Tile(line[i]);
                            ag->getTileBag()->addBack(new_tile);
                        }
                        else
                        {
                            std::cout << "Error with tile read in, Enter appropriate load game file" << std::endl;
                            exit(EXIT_FAILURE);
                        }
                    }
                }
                else if (line_count == 1)
                {
                    if (line.length() == 0)
                    {
                        std::cout << "Error with name read in, Enter appropriate load game file" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        playerNames[PLAYER1_INDEX] = line;
                    }
                }
                else if (line_count == 2)
                {
                    if (line.length() == 0)
                    {
                        std::cout << "Error with name read in, Enter appropriate load game file" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        playerNames[PLAYER2_INDEX] = line;
                    }
                    ag->setPlayerNames(playerNames);
                    ag->printPlayerNames();
                }
                //Reading in turn information
                else if (line_count > 2)
                {
                    ag->addTurn(line);
                }
                ++line_count;
            }
            //Loads in and plays the moves as read provided in the txt file
            ag->loadGame();
            //Plays the game with input from there on if it is not testing mode
            if (testingMode)
            {
                std::cout << std::endl;
                ag->printFactories();
                Player **players = ag->getPlayers();
                for (int i = 0; i < NUM_PLAYERS; ++i)
                {
                    std::string name = players[i]->getName();
                    int score = players[i]->getScore();
                    std::cout << std::endl;
                    std::cout << "Score for Player " << name << ": " << score << std::endl;
                    players[i]->printBoard();
                }
            }
            else
            {
                ag->playGame();
            }
            delete ag;
        }
    }
}

//Handles the printing of the credits
void credits()
{
    std::cout << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << "Name: Thomas Johnstone" << std::endl;
    std::cout << "Student ID: s3781876" << std::endl;
    std::cout << "Email: s3781876@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Owen Griffiths" << std::endl;
    std::cout << "Student ID: s3815261 " << std::endl;
    std::cout << "Email: s3815261@student.rmit.edu.au " << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Jason Tran" << std::endl;
    std::cout << "Student ID: s3840285" << std::endl;
    std::cout << "Email: s3840285@student.rmit.edu.au" << std::endl;
    std::cout << "----------------------------------" << std::endl;
}

//Handles the printing of the quitting message
void eofQuit(bool eof)
{
    if (eof)
    {
        std::cout << std::endl;
    }
    std::cout << "Goodbye" << std::endl;
}