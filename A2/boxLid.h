#ifndef __BOXLID__
#define __BOXLID__

#include "node.h"

class boxLid
{
public:
    boxLid();
    ~boxLid();

    int size();
    void clear();
    Node popFront();
    void addBack(char tile);
    void printboxLid();

private:
    Node* head;
    int length;

};

#endif