#ifndef PLAYERBOARD_H
#define PLAYERBOARD_H

#include <vector>
#include <iostream>
#define MAX_BOARD_COLS 12
#define MAX_BOARD_ROWS 5
//Forward declaration
class Tile;

/**
 * Represents the player board.
 * Contains all the tiles which the player has.
 * 
 * 
 * Not sure about the broken tile section....
 * 
 */

class playerBoard{

    //2D array implementation
    playerBoard();

    //Deep copy of the board
    playerBoard(playerBoard& other);

    //Deletes the board
    ~playerBoard();

    //Adding a tile to the board
    void addTile(Tile* tile, int row, int col);

    //Removing a tile from the board
    void removeTile(int row, int col);

    //Moving the tile on the board
    void moveTile(Tile* tile, int prevRow, int prevCol, int newRow, int newCol);

private:
    char board[MAX_BOARD_ROWS][MAX_BOARD_COLS];
 
};

#endif // PLAYERBOARD_H