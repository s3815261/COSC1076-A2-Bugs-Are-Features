#include <iostream>

int main(void)
{

    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Menu" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Credits (Show student information)" << std::endl;
    std::cout << "4. Quit" << std::endl;
    int option;
    std::cout << std::endl;
    std::cout << ">";
    std::cin >> option;

    while (option > 4 || option < 1)
    {
        std::cout << "Invalid Input" << std::endl;
        std::cout << ">";
        std::cin >> option;
    }
    if (option == 1)
    {
        std::cout << "Starting a New Game" << std::endl;
        std::cout << std::endl;
        std::cout << "Enter a name for player 1" << std::endl;
        std::string player1;
        std::cout << ">";
        std::cin >> player1;
        std::cout << std::endl;
        std::cout << "Enter a name for player 2" << std::endl;
        std::string player2;
        std::cout << ">";
        std::cin >> player2;
        std::cout << std::endl;
        std::cout << "Let's Play!" << std::endl;
    }
    else if (option == 2)
    {
        std::cout << "Enter the filename from which to load a game" << std::endl;
        std::cout << ">";
        std::string filename;
        std::cin >> filename;
    }
    else if (option == 3)
    {
        std::cout << "Name: Thomas Johnstone" << std::endl;
        std::cout << "Student ID: s3781876" << std::endl;
        std::cout << "Email: s3781876@student.rmit.edu.au" << std::endl;
        std::cout << "Name: Owen Griffiths" << std::endl;
        std::cout << "Student ID: " << std::endl;
        std::cout << "Email: " << std::endl;
        std::cout << "Name: Jason Tran" << std::endl;
        std::cout << "Student ID: " << std::endl;
        std::cout << "Email: " << std::endl;
    }
    else if (option == 4)
    {
        std::cout << "Goodbye" << std::endl;
    }
}
