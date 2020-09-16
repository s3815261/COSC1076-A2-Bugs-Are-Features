#ifndef __NODE__
#define __NODE__

#include "tile.h"

class Node
{

public:
    Node(char tile, Node *next);
    ~Node();
    Node(Node &other);

    char tile;
    Node *next;
};

#endif