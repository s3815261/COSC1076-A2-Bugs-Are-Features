#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>
#include <vector>
#include "tile.h"

#define FACTORY_MAX_ARRAY_SIZE 5

class Tile;

class Factory
{

public:
    Factory();

    ~Factory();

    Factory(Factory& other);

    //return the size of the factory vector
    int size();

    //get the ith element from the factory
    Tile* get(int index);

    //add a tile to the end of the factory
    void add(Tile* tile);

    //add a tile to a certain index
    void add(Tile* tile, int index);

    //removing an element from the vector
    void remove(int index);


private:
    std::vector<Tile*> factory;


};

#endif // FACTORY_H