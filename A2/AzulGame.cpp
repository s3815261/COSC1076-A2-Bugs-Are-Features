#include "azulGame.h"

azulGame::azulGame()
{
}

azulGame::~azulGame()
{
}

std::string azulGame::getP1()
{
    return p1.getName();
}
std::string azulGame::getP2()
{
    return p2.getName();
}
tileBag azulGame::getTB()
{
    return tb;
}