#include "node.h"
#include "boxLid.h"
#include <iostream>
#include <limits>

boxLid::boxLid()
{
    head = nullptr;
    length = 0;
}
boxLid::~boxLid()
{
    clear();
}
int boxLid::size()
{
    return length;
}

void boxLid::addBack(char tile)
{
    Node *toAdd = new Node(tile, nullptr);

    if (head == nullptr)
    {
        head = toAdd;
    }
    else
    {
        Node *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = toAdd;
    }
    ++length;
}

void boxLid::printboxLid()
{
    Node *current_node = head;
    while (current_node != nullptr)
    {
        std::cout << current_node->tile << std::endl;
        current_node = current_node->next;
    }
}
void boxLid::clear()
{
    if (head != nullptr)
    {
        Node *current_node = head;
        while (current_node != nullptr)
        {
            //get the next node in the link
            Node *next_node = current_node->next;
            //delete current node
            delete current_node;
            --length;
            //make the current node point to the next node
            current_node = next_node;
        }
    }
    head = nullptr;
}

Node boxLid::getFront()
{
    Node *original_first_node = head;
    Node *new_node = original_first_node->next;
    return *original_first_node;
    head = new_node;
}