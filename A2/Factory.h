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

        int size();

        Tile* get(int index);

        void add(Tile* tile);

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