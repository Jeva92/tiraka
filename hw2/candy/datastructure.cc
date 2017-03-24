//TiRaKa 2nd assignment
//Made by Verneri Ahola opnum. 229681
//This implementation is made with hashtable, so that if the items "collide", the colliding item can be placed
//"behind" the first one. Just like in a linked list where every entry knows its next entry (if any).
//I made this first with objects, but after realizing that the assignment needs linked list kind of implementation too,
//the structure became too slow in my opinion, so i decided to go with structs.

#include "datastructure.hh"
#include <string>
#include <iostream>

//Constructor, which makes all the data in array to NULL.
//This might not be needed. Still wanted to do it like this.
Datastructure::Datastructure()
{
    for (int i = 0; i < STRUCTURE_SIZE; i++) {
          structure[i] = NULL;
    }
}

//Destructor. I'm not 100% sure if this is needed as is, but it was used in one of the
//implementation I found on the internet and it made sense.
//I don't really see a reason why not to use it like this.
Datastructure::~Datastructure()
{
    for (int i = 0; i < STRUCTURE_SIZE; i++) {
        Entry* ptr = structure[i];
        while (ptr != NULL) {
            Entry* ptr_ = ptr->next;
            delete ptr;
            ptr = ptr_;
        }
    }
}

//Function that adds data.
void Datastructure::add(const string &ID, const string &location,
                        unsigned int amount, const string &name)
{
    //Lets make hash from the id.
    int hashi = (hash(ID));
    //And copy the pointer from the array which we will play with.
    Entry* ptr = structure[hashi];
    while (ptr != NULL) {
        //If the ID already exists, then we just add the amount to the existing struct.
        if (ptr->ID == ID) {
            //If so happens that the amount was earlier 0, then we have to change the amount of
            //different kinds of candy.
            if (ptr->lukumaara == 0) {
                ++size;
            }
            ptr->lukumaara = (ptr->lukumaara + amount);
            return;
        } else if (ptr->next == NULL) {
            //If we didn't find existing entry with the same ID, then we will make a new one.
            ptr->next = new Entry;
            ptr = ptr->next;
            ptr->ID = ID;
            ptr->lukumaara = amount;
            ptr->hyllypaikka = location;
            ptr->tuotenimi = name;
            ++size;
            return;
        }
        ptr = ptr->next;
    }
    //And if it so happens that the first entry in the array was already NULL,
    //then we will create the first one.
    structure[hashi] = new Entry;
    structure[hashi]->ID = ID;
    structure[hashi]->lukumaara = amount;
    structure[hashi]->hyllypaikka = location;
    structure[hashi]->tuotenimi = name;
    ++size;
}

//Function that substracts candies.
void Datastructure::substract(const string &ID, unsigned int amount)
{
    //Same as earlier.
    int hashi = (hash(ID));
    Entry* ptr = structure[hashi];
    while (ptr != NULL) {
        //If the Id is found
        if (ptr->ID == ID) {
            //If so happens that the amount of candy being substracted is higher than the amoung
            //of candy in warehouse, then we tell the user that theres not enough candy.
            if (ptr->lukumaara < amount) {
                std::cout << NOT_ENOUGH_CANDY << std::endl;
                std::cout << "Amount: " << ptr->lukumaara << " Shelf: " << ptr->hyllypaikka << std::endl;
                return;
            }
            //Or else we will just substract the amount
            ptr->lukumaara = (ptr->lukumaara - amount);
            std::cout << "Amount: " << ptr->lukumaara << " Shelf: " << ptr->hyllypaikka << std::endl;
            //If the amount of candy goes to 0, we substract 1 from the different kinds of candies.
            if (ptr->lukumaara == 0) {
                --size;
            }
            return;
        }
        ptr = ptr->next;
    }
    //If eveything else "fails", then we can assume that the candy we were trying to substract just doesnt
    //exist in our table.
    std::cout << NOT_AVAILABLE << std::endl;
}

//Function to find a specifis candy
void Datastructure::find(const string &ID) const
{
    //Again same as earlier
    int hashi = (hash(ID));
    Entry* ptr = structure[hashi];
    while (ptr != NULL) {
        if (ptr->ID == ID) {
            //We found the ID, but its amount is 0, so we will tell the user that it is not available.
            if (ptr->lukumaara == 0) {
                std::cout << NOT_AVAILABLE << std::endl;
                return;
            }
            //Or else we just print the info on the screen.
            std::cout << ptr->tuotenimi << " " << ptr->lukumaara << " " << ptr->hyllypaikka << std::endl;
            return;
        }
        ptr = ptr->next;
    }
    //Like earlier, if we get this far in this function we can assume that the candy doesnt exist in our table.
    std::cout << NOT_AVAILABLE << std::endl;
}

//Amount of different candies in the structure. Just a return function with this implementation.
size_t Datastructure::count() const
{
    //Simple but yet so elegant.
    return size;
}

//Function to empty the structure.
void Datastructure::empty()
{
    //Kinda self explanatory. Go through every spot in the array and if there is a pointer
    //then lets destroy the instance behind that pointer and then make the first pointer NULL.
    for (int i = 0; i < STRUCTURE_SIZE; ++i) {
            Entry* ptr = structure[i];
            while (ptr != NULL) {
                Entry* ptr_ = ptr->next;
                delete ptr;
                ptr = ptr_;
            }
            structure[i] = NULL;
    }
    //The structure was emptied, so theres 0 different kinds of candy.
    size = 0;
}

//Hashing function. Found from the internet for the most part. Seems to work well so why not.
int Datastructure::hash(std::string key) const{
    int hash = hash_seed;
    int chars = key.length();
    for (int i = 0; i < chars; ++i) {
        hash = hash_multi * hash + key[i];
    }
    return ((hash & hash_mask) % STRUCTURE_SIZE);
}
