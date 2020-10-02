#include <vector>
#include <iostream>

#include "PlayerBoard.h"
#include "Tile.h"

PlayerBoard::PlayerBoard()
{
    //Inital player board
    char initialBoard[MAX_BOARD_ROWS][MAX_BOARD_COLS] =
    {   
        { ' ', ' ', ' ', ' ', '.', '|', '|', '.', '.', '.', '.', '.', '\0' },
        { ' ', ' ', ' ', '.', '.', '|', '|', '.', '.', '.', '.', '.', '\0' },
        { ' ', ' ', '.', '.', '.', '|', '|', '.', '.', '.', '.', '.', '\0' },
        { ' ', '.', '.', '.', '.', '|', '|', '.', '.', '.', '.', '.', '\0' },
        { '.', '.', '.', '.', '.', '|', '|', '.', '.', '.', '.', '.', '\0' }
    };

    for (int rows = 0; rows < MAX_BOARD_ROWS; ++rows) 
    {
        for (int cols = 0; cols < MAX_BOARD_COLS; ++cols) 
        {
            board[rows][cols] = initialBoard[rows][cols];
        }
    }
}

//deep copy of the player board
PlayerBoard::PlayerBoard(PlayerBoard& other)
{
}

//deletes the playerboard
PlayerBoard::~PlayerBoard()
{
}

//Rules for adding the tile from factory to gameboard....
void PlayerBoard::addTile(Tile* tile, int row, int col)
{
    //validation to check input is within bounds
    if(row < MAX_BOARD_ROWS && row >= 0 && col < MAX_BOARD_ROWS && col >= 0)
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

void PlayerBoard::addTiletoRow(Tile* tile, int row)
{
    // This variable is the index of where the end 
    // of each of the storage rows are at.
    // It is also where the loop starts at.
    int start = INDEX_STORAGE_ROW_END;

    // This variable is the index of where the empty spaces
    // of each of the storage rows are at.
    // It is also where the loop ends at.
    int end = start - row;  
    
    bool placedTile = false;
    for (int i = start; i != end; --i)
    {
        if (!placedTile)
        {
            // As we view the rows as 1 to 5 inclusive, the (row - 1) is to get the index of the row
            // in the array.
            if (board[row - 1][i] == '.')
            {
                board[row - 1][i] = tile->getTile();
                placedTile = true;
            }
        }
    }
}

//Removing a tile from the board
void PlayerBoard::removeTile(int row, int col)
{
    //checking that it is within bounds
    if(row < MAX_BOARD_ROWS && row >=0  && col < MAX_BOARD_ROWS && col >= 0)
    {
        //removing the tile and putting the board in the default state.
        board[row][col] = '.';
        //Not sure if we need to add some kind of discard pile method here... might implement later...

    }
}

//Moving the tile on the board
void PlayerBoard::moveTile(Tile* tile, int prevRow, int prevCol, int newRow, int newCol)
{   
    char tileLetter = tile->getTile();
    //Checking if the row and col is within bounds
    if(newRow < MAX_BOARD_ROWS && newRow >=0  && newCol < MAX_BOARD_ROWS && newCol >= 0)
    {
        board[newRow][newCol] = tileLetter;
        removeTile(prevRow, prevCol);
    }
}

void PlayerBoard::printPlayerBoard()
{
    for (int rows = 0; rows < MAX_BOARD_ROWS; ++rows)
    {
        std::cout << rows + 1 << ": ";
        for (int cols = 0; cols < MAX_BOARD_COLS; ++cols)
        {
            std::cout << board[rows][cols] << ' ';
        }
        std::cout << std::endl;
    }
}
