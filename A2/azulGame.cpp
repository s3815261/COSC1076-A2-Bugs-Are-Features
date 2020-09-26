#include "azulGame.h"

AzulGame::AzulGame()
{
}

AzulGame::~AzulGame()
{
}

std::string AzulGame::getP1()
{
    return p1.getName();
}

std::string AzulGame::getP2()
{
    return p2.getName();
}

TileBag AzulGame::getTB()
{
    return tb;
}
