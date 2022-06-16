#include "DoubleLinkedBag.h"

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
bool DoubleLinkedBag<ItemType>::add(const ItemType& newEntry) //adds to front of chain (top of bag) DONE
{
    Node<ItemType>* nextNodePtr = new Node<ItemType>(newEntry, headPtr, nullptr);

    if (headPtr != nullptr)
        headPtr->setPrev(nextNodePtr);

    headPtr = nextNodePtr;

    nextNodePtr = nullptr;

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
    Node<ItemType>* nodeToDeletePtr = getPointerTo(anEntry, headPtr);

    if (!isEmpty() && (nodeToDeletePtr != nullptr))
    {
        if ((headPtr == nodeToDeletePtr) && (headPtr != tailPtr)) //if node is first node and there are >1 node in bag
        {
            headPtr = nodeToDeletePtr->getNext();
            headPtr->setPrev(nullptr);
        }
        else if (tailPtr == nodeToDeletePtr) //if node is last node or there is 1 node in bag
        {
            tailPtr = nodeToDeletePtr->getPrev();
            tailPtr->setNext(nullptr);
        }
        else //if node is not first and not last
        {
            Node<ItemType>* tempPtr = nodeToDeletePtr->getNext();
            tempPtr->setPrev(nodeToDeletePtr->getPrev());

            tempPtr = nodeToDeletePtr->getPrev();
            tempPtr->setNext(nodeToDeletePtr->getNext());

            tempPtr = nullptr;
        }

        // Return node to the system
        nodeToDeletePtr->setNext(nullptr);
        nodeToDeletePtr->setPrev(nullptr);
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;

        itemCount--;

        return true;
    }

    return false;
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
void DoubleLinkedBag<ItemType>::fillVector(std::vector<ItemType>& bagContents, Node<ItemType>* curPtr) const
{
    if (curPtr != nullptr)
    {
        bagContents.push_back(curPtr->getItem());
        fillVector(bagContents, curPtr->getNext());
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
    Node<ItemType>* nextPtrToDelete = nextNodePtr;

    if (nextNodePtr != nullptr)
    {
        nextNodePtr = nextNodePtr->getNext();
        delete nextPtrToDelete;
        nextPtrToDelete = nextNodePtr;

        deallocate(nextNodePtr);
    }
}