#ifndef __TILEBAG__
#define __TILEBAG__

#include "node.h"

class TileBag
{
public:
    TileBag();
    ~TileBag();
    int size();
    void clear();
    Node popFront();
    void addBack(char tile);
    void printtileBag();

private:
    Node* head;
    int length;
};

#endif // __TILEBAG__