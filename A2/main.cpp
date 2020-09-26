#include <iostream>
#include <fstream>
#include "azulGame.h"
#include "player.h"
#include "tileBag.h"

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

// #define NEWGAME 1
// #define LOADGAME 2
// #define CREDITS 3
// #define EXIT 4

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
            if (option == 1)
            {
                newGame();
            }
            else if (option == 2)
            {
                loadGame(ag);
            }
            else if (option == 3)
            {
                credits();
            }
            else if (option == 4)
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
                    ag.getTB().addBack(line[i]);
                }
            }
            else if (line_count == 1)
            {
                line = ag.getP1();
            }
            else if (line_count == 2)
            {
                line = ag.getP2();
            }
            else if (line_count > 2)
            {
                //make turns
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

