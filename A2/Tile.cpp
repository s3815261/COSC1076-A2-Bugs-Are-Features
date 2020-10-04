#include <iostream>
#include "Tile.h"
//Intilizes the tile and what type it is.
Tile::Tile(char tile) :
    tile(tile)
{
}

//Copies the tile
Tile::Tile(Tile& other) :
    tile(other.tile)
{
}

//Deletes the tile
Tile::~Tile()
{
}

//gets a tile
char Tile::getTile()
{
    return tile;
}

