#ifndef PLAYERBOARD_H
#define PLAYERBOARD_H

#include <vector>
#include <iostream>

#define MAX_BOARD_COLS 13
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

class PlayerBoard 
{

    public:
        //2D array implementation
        PlayerBoard();

        //Deep copy of the board
        PlayerBoard(PlayerBoard& other);

        //Deletes the board
        ~PlayerBoard();

        //Adding a tile to the board
        void addTile(Tile* tile, int row, int col);

        //Adding tile to the board starting from the back based on the row selection
        void addTiletoRow(Tile* tile, int row);

        //Removing a tile from the board
        void removeTile(int row, int col);

        //Moving the tile on the board
        void moveTile(Tile* tile, int prevRow, int prevCol, int newRow, int newCol);

        void printPlayerBoard();

private:
    char board[MAX_BOARD_ROWS][MAX_BOARD_COLS];
 
};

#endif // PLAYERBOARD_H