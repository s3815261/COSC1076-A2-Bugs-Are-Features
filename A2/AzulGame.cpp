#include "AzulGame.h"

AzulGame::AzulGame()
{
    tileBag = new TileBag();
}

AzulGame::~AzulGame()
{
    delete tileBag;
}

std::string AzulGame::getPlayer1Name()
{
    return player1.getName();
}

std::string AzulGame::getPlayer2Name()
{
    return player2.getName();
}

TileBag *AzulGame::getTileBag()
{
    return tileBag;
}

void AzulGame::setPlayer1Name(std::string player1Name)
{
    player1.setName(player1Name);
}

void AzulGame::setPlayer2Name(std::string player2Name)
{
    player2.setName(player2Name);
}

void AzulGame::printPlayerNames()
{
    std::cout << "Player 1 name: " << player1.getName() << std::endl;
    std::cout << "Player 2 name: " << player2.getName() << std::endl;
}

void AzulGame::addTurn(Turn turn)
{
    turn_vector.push_back(turn);
}
