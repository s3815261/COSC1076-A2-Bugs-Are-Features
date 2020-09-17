#include <vector>
#include <iostream>
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

    //Returns 2d size of the board
    int size();

    //Adding a tile to the board
    void addTile(Tile* tile, int row, int col);

    //Removing a tile from the board
    void removeTile(Tile* tile, int row, int col);

    //Moving the tile on the board
    void moveTile(Tile* tile, int row, int col);

private:
    std::vector<std::vector<int>> board;
 

};