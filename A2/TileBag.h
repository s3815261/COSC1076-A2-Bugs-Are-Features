#ifndef __TILEBAG__
#define __TILEBAG__

#include "node.h"

class tileBag
{
public:
    tileBag();
    ~tileBag();
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