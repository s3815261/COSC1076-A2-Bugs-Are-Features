#include <iostream>
#include <limits>

#include "TileBag.h"
#include "Node.h"

//constructor
TileBag::TileBag() : 
    length(0)
{
    head = nullptr;
}

//constructor
TileBag::~TileBag()
{
    clear();
}

//size of tile bag
int TileBag::size()
{
    return length;
}

//clears the content of the tile bag
void TileBag::clear()
{
    if (head != nullptr)
    {
        Node *current_node = head;
        while (current_node != nullptr)
        {
            //get the next node in the link
            Node *next_node = current_node->next;
            //delete current node
            delete current_node;
            --length;
            //make the current node point to the next node
            current_node = next_node;
        }
    }
    head = nullptr;
}

//takes off the tile at the front of the tile bag
Tile *TileBag::popFront()
{
    Node *original_first_node = nullptr;
    Node *new_node = nullptr;
    if (head != nullptr)
    {
        original_first_node = head;
        new_node = original_first_node->next;
        head = new_node;
        --length;
        original_first_node->next = nullptr;
    }
    return original_first_node->tile;
}

//adds tiles to the back of the tilebag
void TileBag::addBack(Tile *tile)
{
    Node *toAdd = new Node(tile, nullptr);

    if (head == nullptr)
    {
        head = toAdd;
    }
    else
    {
        Node *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = toAdd;
    }
    ++length;
}

//intialises the tile bag with 100 tiles of different colours
void TileBag::initaliseTileBag()
{
    char colours[5] = {'R','B','Y','L','U'};
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 5; ++j) {
            Tile* new_tile = new Tile(colours[j]);
            addBack(new_tile);
        }
    }
    
}

//saves the tile bag
std::string TileBag::saveTileBag()
{
    Node *current_node = head;
    std::string tileBag = "";
    while (current_node != nullptr)
    {
        char tile = current_node->tile->getTile();
        tileBag.push_back(tile);
        current_node = current_node->next;
    }
    return tileBag;
}

//prints the contents of the tile bag
void TileBag::printTileBag()
{
    Node *current_node = head;
    while (current_node != nullptr)
    {
        std::cout << current_node->tile->getTile() << std::endl;
        current_node = current_node->next;
    }
}
