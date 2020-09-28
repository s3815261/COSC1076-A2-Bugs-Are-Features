#include "Player.h"

Player::Player() :
    name("Unnamed"),
    score(0)
{
    playerBoard = new PlayerBoard();
}

Player::Player(std::string name) :
    name(name),
    score(0)
{    
    playerBoard = new PlayerBoard();
}

Player::Player(std::string name, int score) :
    name(name),
    score(score)
{
    playerBoard = new PlayerBoard();
}

Player::~Player() 
{
    delete playerBoard;
}

std::string Player::getName() 
{
    return name;
}

void Player::setName(std::string newName)
{
    name = newName;
}

int Player::getScore()
{
    return score;
}

void Player::setScore(int score) 
{
    this->score = score;
}

void Player::addScore(int increment) 
{
    if (increment > 0)
    {
        score += increment;
    }
}

PlayerBoard* Player::getPlayerBoard()
{
    return playerBoard;
}
