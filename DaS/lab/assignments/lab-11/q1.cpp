#include <iostream>

using namespace std;

// --- Node Structure for Linked List (Chain) ---

class node {
public:
    string key;
    string name; // Used as the value associated with the key
    node* next;

    // Constructor to initialize a new node
    node(string k = "", string n = "") : key(k), name(n), next(nullptr) {}
};

// --- Hash Table Class ---

class hashTable {
private:
    // Array of node pointers (heads of the linked lists/chains)
    node **table; 
    int current_size; // Stores the number of buckets/slots

    /**
     * Calculates the hash index for a given key string.
     * Hash Function: (SUM of ASCII values) MOD current_size
     * @param key The string key to hash.
     * @return The hash index (0 to current_size - 1).
     */
    int getHashIndex(const string& key) {
        int sum_ascii = 0;
        for (char k : key) {
            sum_ascii += static_cast<int>(k);
        }
        // Apply the modulo operation to fit it within the table size
        return sum_ascii % this->current_size;
    }

public:
    // Constructor: Initializes the hash table array
    hashTable(int size = 10) {
        this->current_size = size;
        // Allocate memory for the array of head pointers
        table = new node*[this->current_size];
        
        // IMPORTANT FIX: Initialize all head pointers to nullptr
        for (int i = 0; i < this->current_size; i++) {
            table[i] = nullptr;
        }
        cout << "Initialized Hash Table with " << this->current_size << " buckets." << endl;
    }

    // Destructor: Clean up all dynamically allocated memory
    ~hashTable() {
        for (int i = 0; i < this->current_size; i++) {
            node* current = table[i];
            while (current != nullptr) {
                node* to_delete = current;
                current = current->next;
                delete to_delete;
            }
        }
        delete[] table; // Delete the array of pointers
        cout << "Hash Table memory cleaned up." << endl;
    }

    // Insert function
    void insert(string key, string name) {
        int index = getHashIndex(key);
        
        // The problem description implies simple insertion without checking for duplicates 
        // in the specific chain to show the chaining process. 
        
        // 1. Create the new node
        node *newNode = new node(key, name);

        // 2. Insert at the head of the list at the calculated index (Chain Hashing)
        // Set the new node's next pointer to point to the current head (which could be nullptr)
        newNode->next = this->table[index];
        
        // 3. Update the table slot to point to the new node (making it the new head)
        this->table[index] = newNode;
        
        cout << "[Hash: " << index << "] Inserted key \"" << key << "\" with value \"" << name << "\"" << endl;
    }

    // Optional: A display function to show the structure
    void display() {
        cout << "\n--- Current Hash Table State ---\n";
        for (int i = 0; i < this->current_size; i++) {
            node* current = this->table[i];
            if (current != nullptr) {
                cout << "Index " << i << ": ";
                while (current != nullptr) {
                    cout << "(" << current->key << ", " << current->name << ")";
                    if (current->next != nullptr) {
                        cout << " -> ";
                    }
                    current = current->next;
                }
                cout << endl;
            }
        }
        cout << "--------------------------------\n";
    }
    
    // The resize function was complex and not essential for the core logic of chain hashing, 
    // especially without a load factor check. It is omitted for a barebones implementation.
};


// --- Main Execution ---

int main() {
    // 1. Calculate ASCII sums for keys:
    // "A": 65. Index: 65 % 10 = 5
    // "B": 66. Index: 66 % 10 = 6
    // "C": 67. Index: 67 % 10 = 7
    // "AA": 65 + 65 = 130. Index: 130 % 10 = 0 (Example for collision)

    hashTable myhash(10); // Initialize with 10 buckets

    cout << "\n--- Inserting Records ---\n";
    myhash.insert("A", "aaaaa"); 
    myhash.insert("B", "bbbbb");
    myhash.insert("C", "ccccc");
    
    // (Index 5 - Collision/Duplicate)
    myhash.insert("A", "zzzzz"); // This will be chained at index 5
    
    //
    myhash.insert("K", "kkkkk"); // "K": 75. Index: 75 % 10 = 5
    
    cout << "\n--- Demonstrating Chaining ---\n";
    myhash.display(); 
    
    return 0;
}