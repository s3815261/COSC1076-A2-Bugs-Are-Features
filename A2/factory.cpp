#include "factory.h"
#include <iostream>
#include <fstream>

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
    factory.clear();
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
        tile = factory[index];
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
    if(index >= 0 && index < size())
    {
        for(int i = index; i != size(); ++i)
        {
            if(i < size() - 2)
            {
                factory[i] = factory[i+1];
            }
        }

        factory.pop_back();
    }
}

