#include "Node.h"

Node::Node(char tile, Node* next) 
{
    this->tile = tile;
    this->next = next;
}
    
Node::~Node() 
{
}