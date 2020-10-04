#include "Player.h"

//Constructor
Player::Player(std::string name) :
    name(name),
    score(0)
{    
    playerBoard = new PlayerBoard();
}

//Destructor
Player::~Player() 
{
    delete playerBoard;
}

//Gets the player name
std::string Player::getName() 
{
    return name;
}

//Sets the player name
void Player::setName(std::string newName)
{
    name = newName;
}

//Gets the player score
int Player::getScore()
{
    return score;
}

//Sets the player score
void Player::setScore(int score) 
{
    this->score = score;
}

//Gets the playerboard pointer
PlayerBoard* Player::getPlayerBoard()
{
    return playerBoard;
}

//Prints the storagerow, mosaic wall and broken
void Player::printBoard()
{
    std::cout << "Mosaic for " << name << ":" << std::endl;
    playerBoard->printPlayerBoard();
    std::cout << std::endl;
}
