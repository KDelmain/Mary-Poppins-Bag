#include "BagInterface.h"
#include "DoubleLinkedBag.h"
#include <iostream>
#include <string>
#include <string.h>
#include <cctype>
#include <algorithm>
#include <random>

using namespace std;

void shakeBag(BagInterface<string>* bagPtr); // Tells user how many items in the bag    TODO shuffle items in bag when shaken
void peekIntoBag(BagInterface<string>* bagPtr); // Shows user the contents of the bag   TODO randomize number and show the user that many of the first items
void addItem(BagInterface<string>* bagPtr); // Adds an item to the bag
void removeItem(BagInterface<string>* bagPtr); // TODO Removes an item from the bag, allow the user to search for specific item

int generateMenu(BagInterface<string>* bagPtr); // Menu options
void initializeBag(BagInterface<string>* bagPtr); // Fills the bag with a few items
//void scrambleContents(BagInterface<string>* bagPtr); // TODO Reorders the bag contents, will be called in shakeBag()

int main()
{
    int menuSelection;
    BagInterface<string>* bagPtr = nullptr;
    bagPtr = new DoubleLinkedBag<string>();

    initializeBag(bagPtr);

    cout << "You've found a mysterious bag!\n\n";

    do
    {
        menuSelection = generateMenu(bagPtr);

    } while (menuSelection != 5);

	return 0;
}

int generateMenu(BagInterface<string>* bagPtr)
{
    int entry;

    cout << "Would you like to . . .\n\n";

    cout << "1. Shake the bag\n";
    cout << "2. Peek inside of the bag\n";
    cout << "3. Put an item into the bag\n";
    cout << "4. Take an item out of the bag\n";
    cout << "5. Leave\n" << endl;

    cin >> entry;

    switch (entry)
    {
        case 1:
            cout << "\nYou pick up the bag and give it a few hearty shakes!\n" << endl;
            shakeBag(bagPtr);
            //scrambleContents(bagPtr);
            break;
        case 2:
            cout << "\nYou unclasp the bag and peer inside . . .\n" << endl;
            peekIntoBag(bagPtr);
            break;
        case 3:
            cout << "\nYou decide to put an item into the bag!\n" << endl;
            addItem(bagPtr);
            break;
        case 4:
            cout << "\nYou decide to take an item out of the bag!\n" << endl;
            removeItem(bagPtr);
            break;
        case 5:
            cout << "\nYou figure it's best to leave the mysterious bag alone for now.\n\n" << endl;
            cout << "Perhaps you'll come across it again someday . . ." << endl;
            bagPtr->clear();
            break;
    }

    return entry;
}

void shakeBag(BagInterface<string>* bagPtr)
{
    cout << "It feels like there is about " << bagPtr->getCurrentSize() << " items in the bag.\n" << endl;
}

void peekIntoBag(BagInterface<string>* bagPtr)
{
    cout << "You see:\n";

    vector<string> bagItems = bagPtr->toVector();

    // This displays the items in a neat list, with commas, the word "and", and a period where appropriate 
    int numberOfEntries = (int)bagItems.size();
    for (int i = 0; i < numberOfEntries; i++)
    {
        if (numberOfEntries == 1)
        {
            cout << bagItems[i] << ".";
        }
        else
        {
            if (i == numberOfEntries - 1)
            {
                cout << "and " << bagItems[i] << ".";
            }
            else
            {
                if (numberOfEntries == 2)
                {
                    cout << bagItems[i] << " ";
                }
                else
                {
                cout << bagItems[i] << ", ";
                }
            }
        }
    }
    
    cout << "\n" << endl;
}

void addItem(BagInterface<string>* bagPtr)
{
    string newItem;

    cout << "What item do you want to put into the bag?" << endl;
    getline(cin, newItem); //Temp fix for \n getting stuck in the buffer that I can't clear :(
    getline(cin, newItem);

    //included to make the list of items singular and with the appropriate "a" or "an"
    char firstLetter = tolower(newItem[0]);

    if ((firstLetter == 'a') || (firstLetter == 'e') || (firstLetter == 'i') || (firstLetter == 'o') || (firstLetter == 'u'))
    {
        newItem = "an " + newItem;
    }
    else
    {
        newItem = "a " + newItem;
    }

    cout << "\n\nYou put " << newItem << " into the bag.\n" << endl; 

    bagPtr->add(newItem);
}

void removeItem(BagInterface<string>* bagPtr)
{
    int selection;

    cout << "What item would you like to take out of the bag?\n" << endl;

    vector<string> bagItems = bagPtr->toVector();

    int numberOfEntries = (int)bagItems.size();
    for (int i = 0; i < numberOfEntries; i++)
    {
        cout << (i + 1) << ". " << bagItems[i] << endl;
    }

    cout << "\n";
    cin >> selection;

    bagPtr->remove(bagItems[selection - 1]);

    cout << "\n\nYou took out " << bagItems[selection - 1] << " from the bag.\n" << endl;
}

void initializeBag(BagInterface<string>* bagPtr) //will change this to read to and from a .txt file eventually
{
    string items[] = {"a bottle of medicine", "a lamp", "an umbrella", "a house plant", "a mirror", "a coat rack"};

    for (int i = 0; i < size(items); i++)
    {
        bagPtr->add(items[i]);
    }
}

/* TODO - Throws error (random_device: attempting to reference a deleted fucntion) will check installed C++ packages and see if fixed
void scrambleContents(BagInterface<string>* bagPtr)
{
    vector<string> bagItems = bagPtr->toVector();
    bagPtr->clear();

    auto rd = std::random_device{};
    auto rng = std::default_random_engine{ rd() };

    shuffle(bagItems.begin(), bagItems.end(), rng);

    for (int i = 0; i < size(bagItems); i++)
    {
        bagPtr->add(bagItems[i]);
    }
}
*/