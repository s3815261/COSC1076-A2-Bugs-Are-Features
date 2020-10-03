#ifndef __TILEBAG__
#define __TILEBAG__

#include "Node.h"

#define MAX_TILES   20

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
    void initaliseTileBag();
    std::string saveTileBag();

private:
    Node* head;
    int length;
};

#endif // __TILEBAG__