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
void credits();
void eofQuit(bool eof);
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
    ag.playGame(false);
}

// void mulitply(int a, int b);

// multiply(a,b);


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
                    Tile* new_tile = new Tile(line[i]);
                    ag.getTileBag()->addBack(new_tile);
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
                std::vector<std::string> string_split = split(line);
                int factory_number = -1;
                char tile_colour = 'A';
                int row = -1;
                int string_split_size = string_split.size();
                for (int i = 1; i < string_split_size; ++i)
                {
                    if (i == 1)
                    {
                        factory_number = std::stoi(string_split[i]);
                    }
                    else if (i == 2)
                    {
                        tile_colour = string_split[i][0];
                    }
                    else if (i == 3)
                    {
                        row = std::stoi(string_split[i]);
                    }
                }
                
                Turn turn = {factory_number, tile_colour, row};
                ag.addTurn(turn);
             
            }
            ++line_count;
        }
    }
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