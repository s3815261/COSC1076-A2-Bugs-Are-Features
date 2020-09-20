#include "tile.h"
#include <iostream>
 //Intilizes the tile and what type it is.
   Tile::Tile(Type type, char tile)
   {
       this->type = type;
       this->tile = tile;

   }
   
   //Copies the tile
   Tile::Tile(Tile& other)
   {
       this->type = other.type;
   }

   //Deletes the tile
   Tile::~Tile()
   {

   }

   //Gets the type of tile
   Type Tile::getType()
   {
       return type;
   }

  char Tile::getTile()
  {
      return tile;

  }
