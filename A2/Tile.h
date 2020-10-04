#ifndef TILE_H
#define TILE_H

class Tile {
public:
   Tile(char tile);
   ~Tile();

   char getTile();

private:
   //Stores what type the tile is
   char tile;
   
};


#endif // TILE_H