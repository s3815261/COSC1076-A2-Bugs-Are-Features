#ifndef PLAYERBOARD_H
#define PLAYERBOARD_H

#define MAX_BOARD_COLS              12
#define MAX_BOARD_ROWS              5
#define MAX_MOSAIC_COLS             5
#define MAX_MOSAIC_ROWS             5
#define INDEX_STORAGE_ROW_END       4
#define INDEX_MOSAIC_WALL_START     7
#define INDEX_FIRST_ROW             0
#define INDEX_LAST_ROW              4

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
        PlayerBoard();
        ~PlayerBoard();

        Factory* getBroken();

        void addTileToStorageRow(Tile* tile, int row);

        void addTileToMosaic(Tile* tile, int row);

        void removeTile(int row, int col);

        Tile* popTileFromStorageRow(int row);

        Tile* getStorageRowTile(int row);

        bool isStorageRowFull(int row);

        int countAdjacentTilesVertical(int row, int col);

        int countAdjacentTilesHorizontal(int row, int col);

        int getTileColumnOnMosaic(char tileChar, int row);

        void clearStorageRow(int row);
        
        void clearBroken();

        void printPlayerBoard();

private:
    char board[MAX_BOARD_ROWS][MAX_BOARD_COLS];
    char mosaicWall[MAX_BOARD_ROWS][MAX_BOARD_COLS];
    Factory* broken;
 
};

#endif // PLAYERBOARD_H