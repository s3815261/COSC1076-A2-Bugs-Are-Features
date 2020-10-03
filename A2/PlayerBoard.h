#ifndef PLAYERBOARD_H
#define PLAYERBOARD_H

#define MAX_BOARD_COLS              12
#define MAX_BOARD_ROWS              5
#define MAX_MOSAIC_COLS             5
#define MAX_MOSAIC_ROWS             5
#define INDEX_STORAGE_ROW_END       4
#define INDEX_MOSAIC_WALL_START     7

//Forward declaration
class Tile;
class Factory;

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

        Factory* getBroken();

        //Adding a tile to the board
        void addTile(Tile* tile, int row, int col);

        //Adding tile to the board starting from the back based on the row selection
        void addTiletoRow(Tile* tile, int row);

        void addTiletoMosaic(Tile* tile, int row);

        Tile* popTileFromStorageRow(int row);

        //Removing a tile from the board
        void removeTile(int row, int col);

        //Moving the tile on the board
        void moveTile(Tile* tile, int prevRow, int prevCol, int newRow, int newCol);

        void printPlayerBoard();

        Tile* getStorageRowTile(int row);

        bool isStorageRowFull(int row);

        void clearStorageRow(int row);

private:
    char board[MAX_BOARD_ROWS][MAX_BOARD_COLS];
    char mosaicWall[MAX_BOARD_ROWS][MAX_BOARD_COLS];
    Factory* broken;
 
};

#endif // PLAYERBOARD_H