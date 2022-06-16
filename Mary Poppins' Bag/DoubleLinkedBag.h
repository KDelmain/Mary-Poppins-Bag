#ifndef DOUBLE_LINKED_BAG_H
#define DOUBLE_LINKED_BAG_H

#include "BagInterface.h"
#include "Node.h"
#include <cstddef>

template<class ItemType>
class DoubleLinkedBag : public BagInterface<ItemType> // TODO - remove function
{
private:
    Node<ItemType>* headPtr; //Pointer to the first node
    Node<ItemType>* tailPtr; //Pointer to the last node
    int itemCount; //Number of items in the bag

    void fillVector(std::vector<ItemType>& bagContents, Node<ItemType>* curPtr) const;

    Node<ItemType>* getPointerTo(const ItemType& target, Node<ItemType>* curPtr) const;

    void deallocate(Node<ItemType>* nextNodePtr);

public:
    DoubleLinkedBag();
    virtual ~DoubleLinkedBag();
    int getCurrentSize() const;
    bool isEmpty() const;
    bool add(const ItemType& newEntry);
    bool remove(const ItemType& anEntry);
    void clear();
    bool contains(const ItemType& anEntry) const;
    std::vector<ItemType> toVector() const;
};

#include "DoubleLinkedBag.cpp"
#endif