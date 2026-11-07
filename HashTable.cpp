#include <iostream>

#include "HashTable.h"

using namespace std;

// Compute the hash value for a given key
int HashTable::hashFunction(string key) const {
        int hash = 0;
        // Compute the hash by summing the ASCII values of the characters in the key
        for (int i = 0; i < key.length(); i++) {
            hash += static_cast<int>(key[i]);
        }
        hash = hash % TABLE_SIZE; // Ensure the hash is within the table size

        return hash;
    }

// Normalize the facility ID for hashing
string HashTable::normalizeId(string id) const {
    // remove whitespace and convert to uppercase
    string normalizedId;
    for (char c : id) {
        if (!isspace(c) && c != '\n' && c != '\r' && c != '\t') {
            normalizedId += c;
        }
    }
    normalizedId[0] = toupper(normalizedId[0]);
    return normalizedId;
}

// Constructor
HashTable::HashTable(vector<Facilities> facilities) {
    for (const Facilities& facility : facilities) {
        int index = hashFunction(normalizeId(facility.getId())); // Used hash function to determine the initial index
        while (true){
            // Check if the current index is empty
            if (table[index].empty()){ 
                table[index].push_back(facility);
                break;
            }
            // Handle collision by probing the next index
            else {
                collisions++;
                index = (index + 1);
                if (index >= TABLE_SIZE) {
                    index = 0;
                }
            }
        }
    }
}

// Search for a facility using its ID and the hash function
Facilities HashTable::SearchUsingHash(string id) const {
    id = normalizeId(id); // Normalize the ID before hashing
    int index = hashFunction(id); // Used hash function to determine the initial index
    while (true){
        // If the current index is empty, the facility is not found
        if (table[index].empty()){
         cout << "Facility not found." << endl;
         return Facilities("", "", "", ""); // Return an empty facility if not found
        }
        // Return the facility if the ID matches
        else if (table[index][0].getId() == id){
            return table[index][0];
        }
        // Handle collision by probing the next index
        else {
            index = (index + 1);
            if (index >= TABLE_SIZE) {
                index = 0;
            }
        }
    }
}

// Display the contents of the hash table (mostly for debugging purposes)
void HashTable::DisplayHashTable() const {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << i << ": ";
        if (table[i].empty()) {
            cout << "Empty";
        } 
        else {
            for (const Facilities& facility : table[i]) {
                cout << facility.getId() << " ";
                cout << facility.getFacilityName() << " ";
                cout << facility.getBuildingName() << " ";
                cout << facility.getFacilityType() << " ";
            }
        }
        cout << endl;
    }
}

// Get the number of collisions that have occurred in the hash table
int HashTable::getCollisions() const {
    return collisions;
}

// Get the size of the hash table
int HashTable::getTableSize() const {
    return TABLE_SIZE;
}