#include "player.h"

Player::Player() :
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

void player::setName(std::string newname)
{
    name = newname;
}