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
    Node popFront();
    void addBack(char tile);
    void printTileBag();

private:
    Node* head;
    int length;
};

#endif // __TILEBAG__