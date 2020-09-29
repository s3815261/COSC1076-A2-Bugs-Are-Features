#ifndef __TILEBAG__
#define __TILEBAG__

#include "Node.h"

class TileBag
{
public:
    TileBag();
    ~TileBag();
    int size();
    void clear();
    Tile* popFront();
    void addBack(Tile* tile);
    void printTileBag();
    void initalisedTileBag();

private:
    Node* head;
    int length;
};

#endif // __TILEBAG__