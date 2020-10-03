#include <iostream>
#include <fstream>

#include "Factory.h"

 //initializes the factory
 Factory::Factory()
 {
 }

//Creates a deep copy of the factory
Factory::Factory(Factory& other):
    factory(other.factory)
{
}

//deletes the factory
Factory::~Factory()
{
    for (int i = 0; i < size(); ++i) 
    {
        if (factory[i] != nullptr)
        {
            delete factory[i];
        }
    }
    clearAll();
}

//returns the size of the factory
int Factory::size()
{
    return factory.size();
}

//Gets the tile from a specific index of the factory
Tile* Factory::get(int index)
{
    Tile* tile = nullptr;
    if (index >= 0 && index < size()) 
    {
        if (factory[index] != nullptr)
        {
            tile = factory[index];
        }
    }
    return tile;
}

//Adds tile at a specific index of the factory
void Factory::add(Tile* tile, int index)
{
    if(index >= 0 && index < size())
    {
        factory.insert(factory.begin() + index, tile);
    }
}

//Adds tile to the end of the factory
void Factory::add(Tile* tile)
{
    factory.push_back(tile);
}

//removes a specifc tile from the factory at a certain index
void Factory::remove(int index) 
{
    factory.erase(factory.begin() + index);
}

void Factory::printFactory()
{
    for (int i = 0; i < size(); ++i)
    {
        std::cout << get(i)->getTile() << ' ';
    } 
}

Tile* Factory::popFront()
{
    Tile* tile = nullptr;
    if (size() > 0)
    {
        if (get(0) != nullptr)
        {
            int indexFront = 0;
            tile = get(indexFront);
            remove(indexFront);
        }
    }
    return tile;
}

Tile** Factory::popSameTile(char tile) 
{
    Tile** tiles = new Tile*[MAX_TILES];
    for (int i = 0; i < MAX_TILES; ++i)
    {
        tiles[i] = nullptr;
    }
    int length = 0;
    for (int i = 0; i < size(); ++i) 
    {
        if (get(i)->getTile() == tile)  
        {
            tiles[length] = get(i); // RUBL, R
            ++length;
        }
    }
    std::vector<Tile*> tempVector;
    // for (int i = size() - 1; i > 0; --i) 
    // {
    //     if (get(i) != nullptr) 
    //     {
    //         if (get(i)->getTile() == tile) 
    //         {
    //             factory[i] = nullptr; // nullptr UBL 
    //             remove(i); 
    //         }
    //         else
    //         {
                
    //         }
    //     }
    // } 
    for (int i = 0; i < size(); ++i) // RUBL
    {
        if (get(i) != nullptr)
        {
            if (get(i)->getTile() != tile)
            {
                tempVector.push_back(get(i)); // UBL
            }
        }
    }
    clearAll();
    int tempVectorSize = tempVector.size();
    for (int i = 0; i < tempVectorSize; ++i)
    {
        add(tempVector[i]);
    }
    setSameTileLength(length);
    return tiles;
}

void Factory::clearAll()
{
    factory.clear();
}

int Factory::getSameTileLength()
{
    return sameTileLength;
}

void Factory::setSameTileLength(int value)
{
    sameTileLength = value;
}
