#ifndef BAG_INTERFACE_H
#define BAG_INTERFACE_H

#include <vector>

template<class ItemType>
class BagInterface
{
    public:

        /************************************************************************
        * Gets the current number of objects in the bag
        *
        * @return   The int number of objects currently in the bag
        ************************************************************************/
        virtual int getCurrentSize() const = 0;

         /************************************************************************
         * Checks if the bag is empty
         *
         * @return   True if the bag is empty, false if the bag contains items
         ************************************************************************/
        virtual bool isEmpty() const = 0;

         /************************************************************************
         * Adds one instance of a given entry to the bag
         *
         * @post    If successful, newEntry is added to the bag and the count of
         *              items in the bag increases by 1
         * @param   [newEntry] The object to be added to the bag as a new entry
         * @return  True if addition was successful, false if addition failed
         ************************************************************************/
        virtual bool add(const ItemType& newEntry) = 0;

         /************************************************************************
         * Removes one instance of a given entry from the bag if possible
         *
         * @post    If successful, anEntry is removed from the bag and the count
         *              of items in the bag decreases by 1
         * @param   [anEntry] The object to be removed from the bag
         * @return  True if removal was successful, false if removal failed
         ************************************************************************/
        virtual bool remove(const ItemType& anEntry) = 0;

         /************************************************************************
         * Removes all objects from the bag
         *
         * @post   The bag contains no objects and the count of items in the bag
         *              is set to 0
         ************************************************************************/
        virtual void clear() = 0;

         /************************************************************************
         * Checks if the bag contains the specified object
         *
         * @param   [anEntry] The object to locate
         * @return  True if the bag contains anEntry, false if not
         ************************************************************************/
        virtual bool contains(const ItemType& anEntry) const = 0;

         /************************************************************************
         * Empties then fills a vector with all the objects that are in the bag
         *
         * @return   A vector that contains all objects in the bag
         ************************************************************************/
        virtual std::vector<ItemType> toVector() const = 0;

         /************************************************************************
         * Destroys the object and frees memory allocated by the object
         ************************************************************************/
        virtual ~BagInterface() {}

};
#endif