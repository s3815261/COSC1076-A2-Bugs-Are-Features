#include "Player.h"

//constructor
Player::Player(std::string name) :
    name(name),
    score(0)
{    
    playerBoard = new PlayerBoard();
}

//deconstructor
Player::~Player() 
{
    delete playerBoard;
}

//gets a players name
std::string Player::getName() 
{
    return name;
}

//sets a players name
void Player::setName(std::string newName)
{
    name = newName;
}

//gets a players score
int Player::getScore()
{
    return score;
}

//sets a players score
void Player::setScore(int score) 
{
    this->score = score;
}

PlayerBoard* Player::getPlayerBoard()
{
    return playerBoard;
}

void Player::printBoard()
{
    std::cout << std::endl;
    std::cout << "Mosaic for " << name << ":" << std::endl;
    playerBoard->printPlayerBoard();
    std::cout << std::endl;
}
