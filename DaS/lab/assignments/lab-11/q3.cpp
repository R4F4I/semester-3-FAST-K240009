/*

Implement the class Hash class having the functionality of insert, delete, search and display using list (built
in library for linked list in C++).


*/
#include <iostream>

using namespace std;

//  Node Structure for Linked List (Chain) 

struct DataEntry {
    string key;
    string value;
    DataEntry* next;

    // Constructor to initialize a new node
    DataEntry(string k = "", string v = "") : key(k), value(v), next(nullptr) {}
};

//  Hash Class 

class Hash {
public:
    int BUCKET_COUNT = 10;
    DataEntry** table; // Array of DataEntry pointers (heads of the linked lists)

    int getHashIndex(string key) {
        long long sum_ascii = 0;
        // Calculate sum of ASCII values
        for (char c : key) {
            sum_ascii += static_cast<int>(c);
        }
        // Return the remainder (hash index)
        return sum_ascii % BUCKET_COUNT;
    }

public:
    // Constructor: Initializes the hash table array
    Hash() {
        // Allocate memory for the array of head pointers
        table = new DataEntry*[BUCKET_COUNT];
        
        // Initialize all head pointers to nullptr
        for (int i = 0; i < BUCKET_COUNT; i++) {
            table[i] = nullptr;
        }
    }

    // Destructor: Clean up all dynamically allocated memory
    ~Hash() {
        for (int i = 0; i < BUCKET_COUNT; i++) {
            DataEntry* current = table[i];
            while (current != nullptr) {
                DataEntry* to_delete = current;
                current = current->next;
                delete to_delete;
            }
        }
        delete[] table; // Delete the array of pointers
    }

    // 1. Insert Function: Adds a new record or updates an existing one
    void insert(string key, string value) {
        int index = getHashIndex(key);
        DataEntry* current = table[index];

        // Check for existing key (Update functionality)
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                cout << "Updated key " << key << " at index " << index << endl;
                return;
            }
            current = current->next;
        }

        // If not found, insert at the head of the chain (O(1) insertion)
        DataEntry* newEntry = new DataEntry(key, value);
        newEntry->next = table[index];
        table[index] = newEntry;
        cout << "Inserted (" << key << ", " << value << ") at index " << index << endl;
    }

    // 2. Delete Function: Removes a record by key
    void deleteKey(string key) {
        int index = getHashIndex(key);
        DataEntry* current = table[index];
        DataEntry* prev = nullptr;

        // Traverse the chain to find the key
        while (current != nullptr) {
            if (current->key == key) {
                // Found the key
                if (prev == nullptr) {
                    // Deleting the head of the list
                    table[index] = current->next;
                } else {
                    // Deleting a middle or end node
                    prev->next = current->next;
                }

                delete current; // Free the memory
                cout << "deleted " << key << " index " << index << endl;
                return;
            }
            prev = current;
            current = current->next;
        }

        // If loop finishes without finding the word
        cout << "Deletion failed for " << key << ": Key not found." << endl;
    }

    // 3. Search Function: Retrieves the value for a key
    string search(string key) {
        int index = getHashIndex(key);
        DataEntry* current = table[index];

        // Traverse the chain
        while (current != nullptr) {
            if (current->key == key) {
                cout << "Search found " << key << ": Value is " << current->value << "" << endl;
                return current->value;
            }
            current = current->next;
        }

        cout << "Search failed for " << key << ": Key not found." << endl;
        return "NOT_FOUND";
    }
    
    // 4. Display Function: Prints the entire table contents
    void display() {
        cout << "\n Hash Table Contents \n";
        bool is_empty = true;
        
        for (int i = 0; i < BUCKET_COUNT; ++i) {
            DataEntry* current = table[i];
            
            if (current != nullptr) {
                is_empty = false;
                cout << "Index " << i << ": ";
                
                // Print the chain
                while (current != nullptr) {
                    cout << "(" << current->key << ", " << current->value << ")";
                    if (current->next != nullptr) {
                        cout << " -> ";
                    }
                    current = current->next;
                }
                cout << endl;
            }
        }
        
        if (is_empty) {
            cout << "The hash table is currently empty." << endl;
        }
        cout << "\n";
    }
};

//  Main Execution 

int main() {
    
    Hash myHash;

    cout << "\n Insertion Examples \n";
    // "A": 65 -> Index 5
    myHash.insert("A", "Apple");
    
    // "K": 75 -> Index 5 (Collision)
    myHash.insert("K", "Kite");
    
    // "U": 85 -> Index 5 (Triple Collision)
    myHash.insert("U", "Umbrella");
    
    // "B": 66 -> Index 6
    myHash.insert("B", "Banana");
    
    // Update existing key
    myHash.insert("A", "Alligator");

    myHash.display();
    
    cout << "\n Search Examples \n";
    myHash.search("K");     // Found
    myHash.search("U");     // Found (in the chain)
    myHash.search("Z");     // Not Found
    
    cout << "\n Deletion Examples \n";
    myHash.deleteKey("K");   // Delete middle node of the chain
    myHash.deleteKey("A");   // Delete head node of the chain
    myHash.deleteKey("Z");   // Not found
    
    myHash.display(); // Show remaining elements (U and B should remain)
    
    myHash.deleteKey("U");
    myHash.deleteKey("B");
    
    myHash.display(); // Should be empty

    return 0;
}