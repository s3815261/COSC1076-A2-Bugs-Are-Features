#ifndef __NODE__
#define __NODE__

#include "tile.h"

class Node
{

public:
    Node(char tile, Node *next);
    ~Node();

    char tile;
    Node *next;
};

#endif // __NODE__