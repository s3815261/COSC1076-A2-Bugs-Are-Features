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
    return factory[index];
}

//Adds tile at a specific index of the factory
void Factory::add(Tile* tile, int index)
{
    //Can't get this method to work with the insert....
    if(factory.size() > 0 && index >= 0 && index < factory.size())
    {
        //factory.insert(index,tile);
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
    if(factory.size() > 0 && index >= 0 && index < factory.size())
    {
        for(int i = index; i != factory.size(); ++i)
        {
            if(i < factory.size() - 2)
            {
                factory[i] = factory[i+1];
            }
        }

        factory.pop_back();
    }
}
