#include "playerboard.h"
#include "tile.h"
#include <iostream>



playerBoard::playerBoard()
{
    //Inital player board
    char board[MAX_BOARD_ROWS][MAX_BOARD_COLS] ={  {'.', '|', '.', '.', '.', '.', '.', '\0'},
                                                    {'.', '.', '|', '.', '.', '.', '.', '.','\0'},
                                                    {'.', '.', '.', '|', '.', '.', '.', '.', '.','\0'},
                                                    {'.', '.', '.', '.', '|', '.', '.', '.', '.', '.','\0'},
                                                    {'.', '.', '.', '.', '.', '|', '.', '.', '.', '.', '.','\0'}

                                                };

}

//deep copy of the player board
playerBoard::playerBoard(playerBoard& other)
{



}

//deletes the playerboard
playerBoard::~playerBoard()
{
    delete board;


}

//gets the size of the board, don't think this is needed?
int playerBoard::size()
{


}

//Rules for adding the tile from factory to gameboard....
void addTile(Tile* tile, int row, int col)
{
    //validation to check input is within bounds
    if(row <= MAX_BOARD_ROWS && row >=0  && col <= MAX_BOARD_ROWS && col >= 0)
    {
        //make sure that the tile being added is not null...
        if(tile != nullptr)
        {
            //board[row][col] = tile.getType();
        }
    }
}

//Removing a tile from the board
void removeTile(Tile* tile, int row, int col)
{

}

//Moving the tile on the board
void moveTile(Tile* tile, int row, int col)
{

}





    