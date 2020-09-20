#include <iostream>

void mainMenu();
void displayPrimaryMenu(bool primaryMenu);
void newGame();
void loadGame();
void credits();
void eofQuit(bool eof);

int main(void)
{
    mainMenu();

    return EXIT_SUCCESS;
}

void mainMenu()
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
                loadGame();
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
    std::string player1;
    std::cout << "> ";
    // No ignore input error due to reading an integer first which gives a "\n" symbol at the end before reading a char or string
    std::cin >> player1;
    std::cout << std::endl;
    std::cout << "Enter a name for player 2" << std::endl;
    std::string player2;
    std::cout << "> ";
    std::cin >> player2;
    std::cout << std::endl;
    std::cout << "Let's Play!" << std::endl;
}

void loadGame()
{
    std::cout << std::endl;
    std::cout << "Enter the filename from which to load a game" << std::endl;
    std::cout << "> ";
    std::string filename;
    // No ignore input error due to reading an integer first which gives a "\n" symbol at the end before reading a char or string
    std::cin >> filename;
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
