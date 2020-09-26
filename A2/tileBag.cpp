#include "tileBag.h"
#include "node.h"
#include <iostream>
#include <limits>

TileBag::TileBag()
{
    head = nullptr;
    length = 0;
}

TileBag::~TileBag()
{
    clear();
}

int TileBag::size()
{
    return length;
}

void TileBag::addBack(char tile)
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

void TileBag::printtileBag()
{
    Node *current_node = head;
    while (current_node != nullptr)
    {
        std::cout << current_node->tile << std::endl;
        current_node = current_node->next;
    }
}

void TileBag::clear()
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

Node TileBag::popFront()
{
    Node *original_first_node = nullptr;
    Node *new_node = nullptr;
    if (head != nullptr) 
    {
        original_first_node = head; 
        new_node = original_first_node->next;
        head = new_node; 
        --length; 
        original_first_node->next = nullptr; 
    }
    return *original_first_node;
}