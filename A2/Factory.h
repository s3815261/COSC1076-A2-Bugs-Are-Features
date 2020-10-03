#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>
#include <vector>
#include "Tile.h"

#define FACTORY_MAX_ARRAY_SIZE  5
#define MAX_TILES               20

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

        void printFactory();

        Tile** popSameTile(Factory &factory, char tile);

        void clearAll();

        int getSameTileLength();

        void setSameTileLength(int value);

    private:
        std::vector<Tile*> factory;
        int sameTileLength;

};

#endif // FACTORY_H