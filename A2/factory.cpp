#include "factory.h"
#include <iostream>
#include <fstream>

 Factory::Factory()
 {


 }

Factory::Factory(Factory& other):
    factory(other.factory)
    {

    }

Factory::~Factory()
{
    factory.clear();
}

int Factory::size()
{
    return factory.size();
}

Tile* Factory::get(int index)
{
    return factory[index];
}

void Factory::add(Tile* tile, int index)
{

}

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
