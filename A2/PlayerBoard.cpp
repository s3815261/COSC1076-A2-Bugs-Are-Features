#include <vector>
#include <iostream>

#include "PlayerBoard.h"
#include "Tile.h"
#include "Factory.h"

//2D array implementation
PlayerBoard::PlayerBoard()
{
    //Inital player board
    char initialBoard[MAX_BOARD_ROWS][MAX_BOARD_COLS] =
    {   
        { ' ', ' ', ' ', ' ', '.', '|', '|', '.', '.', '.', '.', '.' },
        { ' ', ' ', ' ', '.', '.', '|', '|', '.', '.', '.', '.', '.' },
        { ' ', ' ', '.', '.', '.', '|', '|', '.', '.', '.', '.', '.' },
        { ' ', '.', '.', '.', '.', '|', '|', '.', '.', '.', '.', '.' },
        { '.', '.', '.', '.', '.', '|', '|', '.', '.', '.', '.', '.' }
    };

    //Tiles that will be placed in the mosaic wall
    char mosaicTiles[MAX_MOSAIC_ROWS] = { 'B', 'Y', 'R', 'U', 'L' };

    //Loop to copy initialBoard onto the board
    for (int rows = 0; rows < MAX_BOARD_ROWS; ++rows) 
    {
        for (int cols = 0; cols < MAX_BOARD_COLS; ++cols) 
        {
            board[rows][cols] = initialBoard[rows][cols];
        }
    }

    //Loop to set up the mosaic wall
    for (int rows = 0; rows < MAX_MOSAIC_ROWS; ++rows) 
    {
        // MAX_MOSAIC_ROWS is there to make sure that the next row is the previous row shifted to the right.
        int index = MAX_MOSAIC_ROWS - rows; 
        for (int cols = 0; cols < MAX_MOSAIC_COLS; ++cols)
        {
            if (index == MAX_MOSAIC_ROWS && cols < MAX_MOSAIC_COLS) 
            {
                index = 0;
            } 
            mosaicWall[rows][cols] = mosaicTiles[index];
            ++index;
        }
    }
    broken = new Factory();
}

//Deletes the playerboard
PlayerBoard::~PlayerBoard()
{
    delete broken;
}

//Get the broken part of the playerboard
Factory* PlayerBoard::getBroken() 
{
    return broken;
}

//Handles adding the tile to the storage row
void PlayerBoard::addTileToStorageRow(Tile* tile, int row)
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
    for (int cols = start; cols >= end; --cols)
    {
        if (!placedTile)
        {
            if (board[row][cols] == '.')
            {
                board[row][cols] = tile->getTile();
                placedTile = true;
            }
        }
    }
}

//Handles adding the tile to the mosaic wall
void PlayerBoard::addTileToMosaic(Tile* tile, int row)
{
    int start = INDEX_MOSAIC_WALL_START;
    int mosaicIndex = 0;
    for (int cols = start; cols < MAX_BOARD_COLS; ++cols)
    {
        if (tile->getTile() == mosaicWall[row][mosaicIndex])
        {
            board[row][cols] = tile->getTile();
        }
        ++mosaicIndex;
    }
}

//Removing a tile from the board
void PlayerBoard::removeTile(int row, int col)
{
    //Checking that it is within bounds
    if(row < MAX_BOARD_ROWS && row >=0  && col < MAX_BOARD_ROWS && col >= 0)
    {
        //Removing the tile and putting the board in the default state.
        board[row][col] = '.';
    }
}

//Pop the right most tile from the storage row
Tile* PlayerBoard::popTileFromStorageRow(int row)
{
    Tile* tile = nullptr;
    int start = INDEX_STORAGE_ROW_END;
    tile = new Tile(board[row][start]);
    removeTile(row, start);
    return tile;
}

//Get the type of tile already in the storage row
Tile* PlayerBoard::getStorageRowTile(int row)
{
    Tile* tile = nullptr;
    int start = INDEX_STORAGE_ROW_END;
    if (board[row][start] != '.')
    {
        tile = new Tile(board[row][start]);
    }
    return tile;
}

//Checks if the storage row is full
bool PlayerBoard::isStorageRowFull(int row)
{
    bool isFull = true;
    int start = INDEX_STORAGE_ROW_END;  
    int end = start - row; 
    for (int cols = start; cols >= end; --cols) 
    {
        if (board[row][cols] == '.')
        {
            isFull = false;
        }
    }
    return isFull;
}

//Counts the number of tiles that are vectically adjacent to a tile
int PlayerBoard::countAdjacentTilesVertical(int row, int col)
{
    bool isUpEmpty = false;
    bool isDownEmpty = false;
    int count = 0;
    int start = INDEX_FIRST_ROW;
    int end = INDEX_LAST_ROW;
    //Checks to the top of the tile
    for (int upIndex = row - 1; upIndex >= start; --upIndex) 
    {
        if (!isUpEmpty)
        {
            if (board[upIndex][col] != '.')
            {
                ++count;
            }
            else
            {
                isUpEmpty = true;
            }
        }
    }
    //Checks to the bottom of the tile
    for (int downIndex = row + 1; downIndex <= end; ++downIndex) 
    {
        if (!isDownEmpty)
        {
            if (board[downIndex][col] != '.')
            {
                ++count;
            }
            else
            {
                isDownEmpty = true;
            }
        }
    }
    return count;
}

//Counts the number of tiles that are horizontally adjacent to a tile
int PlayerBoard::countAdjacentTilesHorizontal(int row, int col)
{
    bool isLeftEmpty = false;
    bool isRightEmpty = false;
    int count = 0;
    int start = INDEX_MOSAIC_WALL_START;
    int end = MAX_BOARD_COLS;
    //Checks to the left of the tile
    for (int leftIndex = col - 1; leftIndex >= start; --leftIndex)
    {
        if (!isLeftEmpty)
        {
            if (board[row][leftIndex] != '.')
            {
                ++count;
            }
            else
            {
                isLeftEmpty = true;   
            }
        }
    }
    //Checks to the right of the tile
    for (int rightIndex = col + 1; rightIndex < end; ++rightIndex)
    {
        if (!isRightEmpty)
        {
            if (board[row][rightIndex] != '.')
            {
                ++count;
            }
            else
            {
                isRightEmpty = true;   
            }
        }
    }
    return count;
}

//Gets the column index of the tile char
int PlayerBoard::getTileColumnOnMosaic(char tileChar, int row)
{
    bool found = false;
    int colIndex = 0;
    for (int col = INDEX_MOSAIC_WALL_START; col < MAX_BOARD_COLS; ++col)
    {
        if (!found)
        {
            if (board[row][col] == tileChar)
            {
                colIndex = col;
                found = true;
            }
        }
    }
    return colIndex;
}

//Clears the storage row
void PlayerBoard::clearStorageRow(int row)
{
    int start = INDEX_STORAGE_ROW_END;
    int end = start - row;
    for (int cols = start; cols >= end; --cols)
    {
        removeTile(row, cols);
    }
}

//Clears the broken part of the playerboard
void PlayerBoard::clearBroken()
{
    for (int i = 0; i < getBroken()->size(); ++i)
    {
        if (getBroken()->get(i) != nullptr)
        {
            delete getBroken()->get(i);
        }
    }
    getBroken()->clearAll();
}

//Handles printing of the storage row, mosaic wall and broken
void PlayerBoard::printPlayerBoard()
{
    for (int rows = 0; rows < MAX_BOARD_ROWS; ++rows)
    {
        std::cout << rows + 1 << ":";
        for (int cols = 0; cols < MAX_BOARD_COLS; ++cols)
        {
            if (board[rows][cols - 1] == '|' && board[rows][cols] == '|')
            {
                std::cout << board[rows][cols];
            }
            else 
            {
                std::cout << ' ' << board[rows][cols];
            }
        }
        std::cout << std::endl;
    }
    std::cout << "broken: ";
    broken->printFactory();
}
