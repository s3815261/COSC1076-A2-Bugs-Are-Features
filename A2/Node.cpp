#include "Node.h"

//node constructor, has a pointer to a tile and a pointer to the next node in the linked list
Node::Node(Tile* tile, Node* next) :
    tile(tile),
    next(next)
{
}

//node deconstructor
Node::~Node()
{
}