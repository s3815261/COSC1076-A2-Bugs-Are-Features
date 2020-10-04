#include <iostream>
#include <fstream>

#include "Factory.h"

 //Initialises the factory
 Factory::Factory() :
    sameTileLength(0)
 {
 }

//Creates a deep copy of the factory
Factory::Factory(Factory& other):
    factory(other.factory),
    sameTileLength(other.sameTileLength)
{
}

//Deletes the factory
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

//Returns the size of the factory
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

//Adds tile to the end of the factory
void Factory::add(Tile* tile)
{
    factory.push_back(tile);
}

//Removes a specifc tile from the factory at a certain index
void Factory::remove(int index) 
{
    factory.erase(factory.begin() + index);
}

//Gets the length of the same tile array when it pops the tiles
int Factory::getSameTileLength()
{
    return sameTileLength;
}

//Sets the length of the same tile array
void Factory::setSameTileLength(int value)
{
    sameTileLength = value;
}

//Pops the 0th element
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

//Pops the tiles that have the same char as the parameter tile
Tile** Factory::popSameTile(char tile) 
{
    Tile** tiles = new Tile*[MAX_TILES];
    for (int i = 0; i < MAX_TILES; ++i)
    {
        tiles[i] = nullptr;
    }
    int length = 0;
    //Adds the tiles which contain the same char as the parameter tile
    for (int i = 0; i < size(); ++i) 
    {
        if (get(i)->getTile() == tile)  
        {
            tiles[length] = get(i); 
            ++length;
        }
    }
    //Adds the tiles which do not contain the same char as the parameter tile to a temp vector 
    std::vector<Tile*> tempVector;
    for (int i = 0; i < size(); ++i)
    {
        if (get(i) != nullptr)
        {
            if (get(i)->getTile() != tile)
            {
                tempVector.push_back(get(i)); 
            }
        }
    }
    clearAll();
    // Adds the tiles in the tempvector back to the factory vectory
    int tempVectorSize = tempVector.size();
    for (int i = 0; i < tempVectorSize; ++i)
    {
        add(tempVector[i]);
    }
    setSameTileLength(length);
    return tiles;
}

//Clears the factory vector
void Factory::clearAll()
{
    factory.clear();
}

//Prints the tiles in the factory
void Factory::printFactory()
{
    for (int i = 0; i < size(); ++i)
    {
        std::cout << get(i)->getTile() << ' ';
    } 
}
