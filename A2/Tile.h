#ifndef TILE_H
#define TILE_H

class Tile {
public:
   //Intilizes the tile and what type it is.
   Tile(char tile);
   
   //Copies the tile
   Tile(Tile& other);

   //Deletes the tile
   ~Tile();

   char getTile();

private:
  //Stores what type the tile is
   char tile;
   
};


#endif // TILE_H