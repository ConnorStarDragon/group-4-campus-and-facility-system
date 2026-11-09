#include <string>
#include <vector>

#include "Facilities.h"

using namespace std;

class HashTable {
private:
    static const int TABLE_SIZE = 17; // Size of the hash table
    vector<Facilities> table[TABLE_SIZE]; // Array of vectors to handle collisions
    int collisions = 0; // Counter for collisions

    int hashFunction(string key) const; // Hash function to compute the index for a given key

    string normalizeId(string id) const; // Normalize the facility ID for hashing

    public:
    HashTable(vector<Facilities> facilities); // Constructor

    Facilities SearchUsingHash(string id) const; // Search for a facility using the hash function
    
    void DisplayHashTable() const; // for debugging purposes, to display the contents of the hash table

    int getCollisions() const; // Get the number of collisions in the hash table

    int getTableSize() const; // Get the size of the hash table
};