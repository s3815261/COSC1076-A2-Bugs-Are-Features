#include <iostream>
#include "Tile.h"
//Intilizes the tile and what type of tile it is, as in which colour.
Tile::Tile(char tile) :
    tile(tile)
{
}

//Deconstructor allows the tile to be deleted
Tile::~Tile()
{
}

//Function that gets a specific tile and returns that tile
char Tile::getTile()
{
    return tile;
}

