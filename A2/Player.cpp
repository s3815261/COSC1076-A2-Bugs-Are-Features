#include "Player.h"

Player::Player() :
    name("Unnamed"),
    score(0)
{
}

Player::Player(std::string name) :
    name(name),
    score(0)
{    
}

Player::Player(std::string name, int score) :
    name(name),
    score(score)
{
}

Player::~Player() 
{
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
