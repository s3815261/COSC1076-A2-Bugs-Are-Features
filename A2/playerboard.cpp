#include "playerboard.h"
#include "tile.h"
#include <iostream>



playerBoard::playerBoard()
{
    //Inital player board
    char board[MAX_BOARD_ROWS][MAX_BOARD_COLS] ={   {'.', '|', '.', '.', '.', '.', '.', '\0'},
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

//Rules for adding the tile from factory to gameboard....
void playerBoard::addTile(Tile* tile, int row, int col)
{
    //validation to check input is within bounds
    if(row <= MAX_BOARD_ROWS && row >=0  && col <= MAX_BOARD_ROWS && col >= 0)
    {
        //make sure that the tile being added is not null...
        if(tile != nullptr)
        {
            //if all validation is meet add the tile to the board
            //Will be R, Y, B, L, U, F
            char tileLetter = tile->getTile();
            board[row][col] = tileLetter;

        }
    }
}

//Removing a tile from the board
void playerBoard::removeTile(int row, int col)
{
    //checking that it is within bounds
    if(row <= MAX_BOARD_ROWS && row >=0  && col <= MAX_BOARD_ROWS && col >= 0)
    {
        //removing the tile and putting the board in the default state.
        board[row][col] = '.';
        //Not sure if we need to add some kind of discard pile method here... might implement later...

    }
}

//Moving the tile on the board
void playerBoard::moveTile(Tile* tile, int prevRow, int prevCol, int newRow, int newCol)
{   
    char tileLetter = tile->getTile();
    //Checking if the row and col is within bounds
    if(newRow <= MAX_BOARD_ROWS && newRow >=0  && newCol <= MAX_BOARD_ROWS && newCol >= 0)
    {
        board[newRow][newCol] = tileLetter;
        removeTile(prevRow, prevCol);
    }
}







    