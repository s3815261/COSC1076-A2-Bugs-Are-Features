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

        //removing an element from the vector
        void remove(int index);

        int getSameTileLength();

        void setSameTileLength(int value);

        Tile* popFront();

        Tile** popSameTile(char tile);

        void clearAll();

        void printFactory();

    private:
        std::vector<Tile*> factory;
        int sameTileLength;

};

#endif // FACTORY_H