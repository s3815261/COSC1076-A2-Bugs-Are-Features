#include "Node.h"

//node constructor
Node::Node(Tile* tile, Node* next) :
    tile(tile),
    next(next)
{
}

//node deconstructor
Node::~Node()
{
}