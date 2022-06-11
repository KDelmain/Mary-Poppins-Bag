#ifndef NODE_H
#define NODE_H

template<class ItemType>
class Node
{
private:
    ItemType item;
    Node<ItemType>* next;
    Node<ItemType>* prev;

public:
    Node();
    Node(const ItemType& anItem);
    Node(const ItemType& anItem, Node<ItemType>* nextNodePtr, Node<ItemType>* prevNodePtr);
    void setItem(const ItemType& anItem);
    void setNext(Node<ItemType>* nextNodePtr);
    void setPrev(Node<ItemType>* prevNodePtr);
    ItemType getItem() const;
    Node<ItemType>* getNext() const;
    Node<ItemType>* getPrev() const;
};

#include "Node.cpp"
#endif