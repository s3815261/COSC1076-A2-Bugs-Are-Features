#include <iostream>
#include <fstream>
#include <sstream>
#include "AzulGame.h"
#include "Player.h"
#include "TileBag.h"

void game(int argc, char **argv);
void mainMenu();
void displayPrimaryMenu(bool primaryMenu);
void newGame(AzulGame &ag);
void loadGame(AzulGame &ag);
void saveGame(AzulGame &ag);
void credits();
void eofQuit(bool eof);
bool tileCheck(char tile);
std::vector<std::string> split(const std::string &str, char delim = ' ')
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim))
    {
        tokens.push_back(token);
    }
    return tokens;
}

#define NEWGAME 1
#define LOADGAME 2
#define CREDITS 3
#define EXITPROGRAM 4

int main(int argc, char **argv)
{
    game(argc, argv);

    return EXIT_SUCCESS;
}

void game(int argc, char **argv)
{
    if (argc == 1)
    {
        mainMenu();
    }
    else if (argc == 3)
    {
    }
}

void mainMenu()
{
    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "-------------------" << std::endl;
    displayPrimaryMenu(true);
    int option = 0;
    std::string input = "";

    AzulGame ag;

    while (option != 4 && !std::cin.eof())
    {
        if (option != 0)
        {
            displayPrimaryMenu(false);
        }
        option = -1;

        std::cout << "> ";
        getline(std::cin, input);
        if (std::isdigit(input[0]))
        {
            option = std::stoi(input);
        }

        bool validInput = true;
        if (option > 4 || option < 1)
        {
            validInput = false;
        }

        while ((option > 4 || option < 1) && std::cin)
        {
            std::cout << "Invalid Input" << std::endl;
            std::cout << "> ";
            getline(std::cin, input);
            if (std::isdigit(input[0]))
            {
                option = std::stoi(input);
            }
            if (option >= 1 && option <= 4)
            {
                validInput = true;
            }
        }
        if (validInput)
        {
            if (option == NEWGAME)
            {
                newGame(ag);
            }
            else if (option == LOADGAME)
            {
                loadGame(ag);
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

bool tileCheck(char tile){
    bool return_val = false;
    if(tile == 'R' || tile == 'Y' || tile == 'B' || tile == 'L' || tile == 'U'){
        return_val = true;
    }
    return return_val;
}

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

void newGame(AzulGame &ag)
{
    std::cout << std::endl;
    std::cout << "Starting a New Game" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter a name for player 1" << std::endl;
    std::string player1Name;
    std::cout << "> ";
    // No ignore input error due to reading an integer first which gives a "\n" symbol at the end before reading a char or string
    getline(std::cin, player1Name);
    std::cout << std::endl;
    std::cout << "Enter a name for player 2" << std::endl;
    std::string player2Name;
    std::cout << "> ";
    getline(std::cin, player2Name);
    std::cout << std::endl;
    std::cout << "Let's Play!" << std::endl;

    ag.setPlayer1Name(player1Name);
    ag.setPlayer2Name(player2Name);
    //initalises the game
    ag.newGame();
    //plays the game with input
    ag.playGame();
}

void loadGame(AzulGame &ag)
{
    std::cout << std::endl;
    std::cout << "Enter the filename from which to load a game" << std::endl;
    std::cout << "> ";
    std::string filename;
    std::cin >> filename;

    std::ifstream input_file(filename);
    // check if the file has been successfully opened
    if (input_file)
    {
        std::cout << "succesffuly opened file" << std::endl;
        int line_count = 0;
        while (!input_file.eof())
        {
            std::string line;
            getline(input_file, line);
            //for each character, tileBag.addBack(char)
            if (line_count == 0)
            {
                int line_size = line.size();
                for (int i = 0; i < line_size; ++i)
                {
                    if(tileCheck(line[i]) == true) {
                        Tile* new_tile = new Tile(line[i]);
                        ag.getTileBag()->addBack(new_tile);
                    } else {
                        std::cout << "Error with tile value read in, Enter appropriate load game file" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    }
                ag.getTileBag()->printTileBag();
            }
            else if (line_count == 1)
            {
                ag.setPlayer1Name(line);
            }
            else if (line_count == 2)
            {
                ag.setPlayer2Name(line);
                ag.printPlayerNames();
            }
            // readingin turn information
            else if (line_count > 2)
            {
                ag.addTurn(line);
            }
            ++line_count;
        }
        //loads in and plays the moves as read provided in the txt file 
        ag.loadGame();
        //plays the game with input from there on
        ag.playGame();
    }
}

void saveGame(AzulGame &ag)
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
    if(saveFile.is_open())
    {
        //Get the variables to save.....
        std::string tileBag = ag.getTileBag()->saveTileBag();
        std::string player1 = ag.getPlayer1Name();
        std::string player2 = ag.getPlayer2Name();
        std::vector<std::string> turn_vector = ag.getTurns();
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

    //Close the file, should have the saved contents
    saveFile.close();
}

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

void eofQuit(bool eof)
{
    if (eof)
    {
        std::cout << std::endl;
    }
    std::cout << "Goodbye" << std::endl;
}