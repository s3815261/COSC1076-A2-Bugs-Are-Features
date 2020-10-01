#ifndef __NODE__
#define __NODE__

#include "Tile.h"

class Node
{

public:
    Node(Tile* tile, Node* next);
    ~Node();

    Tile* tile;
    Node* next;
};

#endif // __NODE__