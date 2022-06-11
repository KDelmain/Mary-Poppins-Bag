#ifndef DOUBLE_LINKED_BAG_H
#define DOUBLE_LINKED_BAG_H

#include "BagInterface.h"
#include "Node.h"
#include <cstddef>

template<class ItemType>
class DoubleLinkedBag : public BagInterface<ItemType> // TODO - implement tailPtr 
{
    private:
        Node<ItemType>* headPtr; //Pointer to the first node
        Node<ItemType>* tailPtr; //Pointer to the last node
        int itemCount; //Number of items in the bag

        // Fills the vector bagContents with the data in the nodes of
        // the linked chain to which curPtr points.
        void fillVector(std::vector<ItemType>& bagContents, Node<ItemType>* curPtr) const;

        // Locates a given entry within this bag.
        // Returns either a pointer to the node containing a given entry or
        // the null pointer if the entry is not in the bag.
        Node<ItemType>* getPointerTo(const ItemType& target, Node<ItemType>* curPtr) const;

        // Deallocates all nodes assigned to this bag
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


template<class ItemType>
DoubleLinkedBag<ItemType>::DoubleLinkedBag() : headPtr(nullptr), tailPtr(nullptr), itemCount(0)
{}

template<class ItemType>
DoubleLinkedBag<ItemType>::~DoubleLinkedBag()
{
    clear();
}

template<class ItemType>
bool DoubleLinkedBag<ItemType>::isEmpty() const
{
    return (itemCount == 0);
}

template<class ItemType>
int DoubleLinkedBag<ItemType>::getCurrentSize() const
{
    return itemCount;
}

template<class ItemType>
bool DoubleLinkedBag<ItemType>::add(const ItemType& newEntry)
{
    // Add to beginning of chain: new node references rest of chain;
    // (headPtr is null if chain is empty)        
    Node<ItemType>* nextNodePtr = new Node<ItemType>();
    nextNodePtr->setItem(newEntry);
    nextNodePtr->setNext(headPtr);  // New node points to chain

    headPtr = nextNodePtr;          // New node is now first node

    itemCount++;

    return true;
}

template<class ItemType>
std::vector<ItemType> DoubleLinkedBag<ItemType>::toVector() const
{
    std::vector<ItemType> bagContents;
    fillVector(bagContents, headPtr);
    return bagContents;
}

template<class ItemType>
bool DoubleLinkedBag<ItemType>::remove(const ItemType& anEntry)
{
    Node<ItemType>* entryNodePtr = getPointerTo(anEntry, headPtr);
    bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
    if (canRemoveItem)
    {
        // Copy data from first node to located node
        entryNodePtr->setItem(headPtr->getItem());

        // Delete first node
        Node<ItemType>* nodeToDeletePtr = headPtr;
        headPtr = headPtr->getNext();

        // TODO tailPtr

        // Return node to the system
        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;

        itemCount--;
    }

    return canRemoveItem;
}

template<class ItemType>
void DoubleLinkedBag<ItemType>::clear()
{
    deallocate(headPtr);
    headPtr = nullptr;
    tailPtr = nullptr;

    itemCount = 0;
}


template<class ItemType>
bool DoubleLinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
    return (getPointerTo(anEntry, headPtr) != nullptr);
}



/**********************************
*   Private Methods
**********************************/

template<class ItemType>
void DoubleLinkedBag<ItemType>::fillVector(std::vector<ItemType>& bagContents,
    Node<ItemType>* curPtr) const
{
    if (curPtr != nullptr)
    {
        bagContents.push_back(curPtr->getItem());
        fillVector(bagContents, curPtr->getNext()); // STEP 13
    }
}

template<class ItemType>
Node<ItemType>* DoubleLinkedBag<ItemType>::getPointerTo(const ItemType& target, Node<ItemType>* curPtr) const
{
    Node<ItemType>* result = nullptr;
    if (curPtr != nullptr)
    {
        if (target == curPtr->getItem())
            result = curPtr;
        else
            result = getPointerTo(target, curPtr->getNext());
    }

    return result;
}

template<class ItemType>
void DoubleLinkedBag<ItemType>::deallocate(Node<ItemType>* nextNodePtr)
{
    Node<ItemType>* nodeToDeletePtr = nextNodePtr;
    if (nextNodePtr != nullptr)
    {
        nextNodePtr = nextNodePtr->getNext();
        delete nodeToDeletePtr;
        nodeToDeletePtr = nextNodePtr;
        deallocate(nextNodePtr);
    }
}

//#include "DoubleLinkedBag.cpp"
#endif