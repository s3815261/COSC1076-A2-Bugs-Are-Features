#include <iostream>
#include <limits>

#include "TileBag.h"
#include "Node.h"

//Constructor, sets the length of the tilebag to be none and the head points to null.
TileBag::TileBag() : 
    length(0)
{
    head = nullptr;
}

//Deconstructor, clears the tilebag of all tiles.
TileBag::~TileBag()
{
    clear();
}

//Function that returns the length of the tile bag which is how many tiles are in the tile bag.
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

//Takes off the tile at the front of the tile bag
Tile *TileBag::popFront()
{
    //Defines the original first node in the chain and the new node
    Node *original_first_node = nullptr;
    Node *new_node = nullptr;
    //Only possible if there is a tile to be removed.
    if (head != nullptr)
    {
        //Makes the head now point to new node and removes returns the tile at the original first node.
        original_first_node = head;
        new_node = original_first_node->next;
        head = new_node;
        --length;
        original_first_node->next = nullptr;
    }
    return original_first_node->tile;
}

//Adds tiles to the back of the tilebag
void TileBag::addBack(Tile *tile)
{
    //Creates a new node
    Node *toAdd = new Node(tile, nullptr);

    //If head is null then the new tile will also be the front tile
    if (head == nullptr)
    {
        head = toAdd;
    }
    else
    {
        //Loop through and find the back of the list
        Node *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        //Place the new tile at the back of the linked list
        current->next = toAdd;
    }
    //Increment Length
    ++length;
}

//Intialises the tile bag
void TileBag::initaliseTileBag()
{
    //Creates a tile bag of 100 tiles with 20 of each colour.
    //Two for loops that loop through each colour and adds 20 of each to the back of the tile bag.
    char colours[5] = {'R','B','Y','L','U'};
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 5; ++j) {
            Tile* new_tile = new Tile(colours[j]);
            addBack(new_tile);
        }
    }
    
}

//Saves the tile bag
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

//Prints the contents of the tile bag
void TileBag::printTileBag()
{
    //For every node that is not a null pointer, prints out the tile at that node.
    Node *current_node = head;
    while (current_node != nullptr)
    {
        std::cout << current_node->tile->getTile() << std::endl;
        current_node = current_node->next;
    }
}
