#include "AzulGame.h"

AzulGame::AzulGame()
{
    tb = new tileBag();
}

AzulGame::~AzulGame()
{
}

std::string AzulGame::getP1Name()
{
    return p1.getName();
}
std::string AzulGame::getP2Name()
{
    return p2.getName();
}
tileBag *AzulGame::getTB()
{
    return tb;
}

void AzulGame::setP1Name(std::string p1name)
{
    p1.setName(p1name);
}

void AzulGame::setP2Name(std::string p2name)
{
    p2.setName(p2name);
}

void AzulGame::printNames()
{
    std::cout << "Player 1 name: " << p1.getName() << std::endl;
    std::cout << "Player 2 name: " << p2.getName() << std::endl;
}

void AzulGame::addTurn(Turn turn)
{
    turn_vector.push_back(turn);
}