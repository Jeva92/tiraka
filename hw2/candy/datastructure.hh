// Definition of Datastructure class for UDS/Tiraka homework 2 -


#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <string>
using std::string;

const std::string NOT_AVAILABLE = "Product not in warehouse.";
const std::string NOT_ENOUGH_CANDY = "Not enough candy available.";

class Datastructure
{
    public:

    Datastructure();

    ~Datastructure();

    // Adds candies to the datastructure (command "A")
    void add(const std::string& ID, const std::string& location,
            unsigned int amount, const std::string& name);
          
    // Removes candies from the datastructure (command "D")
    void substract(const std::string& ID, unsigned int amount);

    // Finds candy and prints its status (command "F")
    void find(const std::string& ID) const;

    // Returns how many different types of candy the datastructure contains (command "C")
    size_t count() const;

    // Empties the datastructure (command "E")
    void empty();
    
    // Copy constructor is forbidden (not important for this assignment)
    Datastructure(const Datastructure&) = delete;
    // Assignment operator is forbidden (not important for this assignment)
    Datastructure& operator=(const Datastructure&) = delete;
    
private:
    //Size of the structure. In theory you can use any number here and it wont affect the memory use too much
    //with low data amounts.
    static const int STRUCTURE_SIZE = 2000;

    //Struct Entry where the candies info is stored. Entry* next indicates that this works also as linked list.
    //Which I believe was a requirement because the assignment said that the size can't determine the max amount of
    //candies in the structure.
    struct Entry {
        std::string ID;
        unsigned int lukumaara;
        std::string hyllypaikka;
        std::string tuotenimi;
        Entry* next = NULL;
    };
    //The structure itself is just an array of pointers to the struct elements.
    Entry* structure[STRUCTURE_SIZE];

    //The amount of different candies in the array.
    int size = 0;

    //Function that makes the hash for data when put into the table. Function itself was found from the internet.
    int hash(std::string key) const;
    //constants needed for the hash. Found the hash function from internet.
    const int hash_seed = 5381;
    const int hash_multi = 33;
    const int hash_mask = unsigned(-1) >> 1;
};

#endif
