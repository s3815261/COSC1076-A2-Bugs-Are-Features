#ifndef TILE_H
#define TILE_H

enum Type {
   RED,
   YELLOW,
   DARK_BLUE,
   LIGHT_BLUE,
   BLACK,
   FIRST_PLAYER,
   NO_TILE
};

class Tile {
public:
   //Intilizes the tile and what type it is.
   Tile(Type type, char tile);
   
   //Copies the tile
   Tile(Tile& other);

   //Deletes the tile
   ~Tile();

   //Gets the type of tile
   Type getType();

   char getTile();

private:
  //Stores what type the tile is
   Type type;
   char tile;
};


#endif