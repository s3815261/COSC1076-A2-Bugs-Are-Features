#include "Node.h"

Node::Node(char tile, Node* next) :
    tile(tile),
    next(next)
{
}
    
Node::~Node() 
{
}