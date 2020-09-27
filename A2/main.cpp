#include <iostream>
#include <fstream>

#include "AzulGame.h"
#include "Player.h"
#include "TileBag.h"

#define NEWGAME         1
#define LOADGAME        2
#define CREDITS         3
#define EXITPROGRAM     4

void mainMenu(AzulGame &ag);
void displayPrimaryMenu(bool primaryMenu);
void newGame();
void loadGame(AzulGame &ag);
void credits();
void eofQuit(bool eof);

int main(void)
{
    AzulGame ag;
    mainMenu(ag);

    return EXIT_SUCCESS;
}

void mainMenu(AzulGame &ag)
{
    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "-------------------" << std::endl;
    displayPrimaryMenu(true);
    int option = 0;

    while (option != 4 && !std::cin.eof())
    {
        if (option != 0)
        {
            displayPrimaryMenu(false);
        }
        option = -1;

        std::cout << "> ";
        std::cin >> option;

        bool validInput = true;
        if (option > 4 || option < 1)
        {
            validInput = false;
        }

        while ((option > 4 || option < 1) && std::cin)
        {
            std::cout << "Invalid Input" << std::endl;
            std::cout << "> ";
            std::cin >> option;
            if (option >= 1 && option <= 4)
            {
                validInput = true;
            }
        }
        if (validInput)
        {
            if (option == NEWGAME)
            {
                newGame();
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

void newGame()
{
    std::cout << std::endl;
    std::cout << "Starting a New Game" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter a name for player 1" << std::endl;
    std::string p1;
    std::cout << "> ";
    // No ignore input error due to reading an integer first which gives a "\n" symbol at the end before reading a char or string
    std::cin >> p1;
    std::cout << std::endl;
    std::cout << "Enter a name for player 2" << std::endl;
    std::string p2;
    std::cout << "> ";
    std::cin >> p2;
    std::cout << std::endl;
    std::cout << "Let's Play!" << std::endl;
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
                    ag.getTB()->addBack(line[i]);
                }
                ag.getTB()->printtileBag();
            }
            else if (line_count == 1)
            {
                ag.setP1Name(line);
            }
            else if (line_count == 2)
            {
                ag.setP2Name(line);
            }
            // readingin turn information
            else if (line_count > 2)
            {
                int factory_number;
                char tile_colour;
                int row;
                int line_size = line.size();

                for (int i = 0; i < line_size; ++i) {
                    if (i == 5) {
                        factory_number = line[5];
                    } else if (i == 7) {
                        tile_colour = line[7];
                    } else if (i == 9) {
                        row = line[9];
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

