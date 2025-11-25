/* 
 Task # 2:
Some ABC university students want to develop an ASCII code-based dictionary app for their Final Year
Project. This app should allow the users to perform the following operations:
a) Add_Record () This function will take a string input from user and add into the dictionary. For adding
the string user will use a unique hash function k MOD 100 (table size must be 100, for k user will calculate
the SUM of ASCII character of that word).
b) Word_Search () User will only pass a single string. If string is not available then generate an error
message.
c) Print_Dictionary () Users can also display the complete dictionary.
Note: Use Separate Chaining in case of collisions.
Output:
    search key AB: FASTNU
    key EF deleted successfully !
    index 31: (AB, FASTNU)
    index 35: (CD, CS)

*/

#include <iostream>
#include <string> // Required for string type

using namespace std;

// --- Data Structures for Dictionary (Hash Table) ---

// 1. Dictionary Entry (Node for the Linked List)
struct DictionaryEntry {
    string key;
    string value;
    DictionaryEntry* next;
};

// 2. Hash Table (Array of Linked Lists)
const int TABLE_SIZE = 100;
DictionaryEntry* hashTable[TABLE_SIZE] = {nullptr}; // Array of pointers to DictionaryEntry

// --- Hash Function ---

/**
 * Calculates the hash index for a given string.
 * Hash is the sum of ASCII values of all characters, k, 
 * modulo the table size (100).
 * @param str The string key to hash.
 * @return The hash index (0 to 99).
 */
int calculate_hash(const string& str) {
    long long sum_ascii = 0; // Use long long for sum to avoid overflow, although unlikely for typical words
    for (char c : str) {
        // Explicitly cast char to int for ASCII value
        sum_ascii += static_cast<int>(c);
    }
    // The hash function is k MOD 100
    return sum_ascii % TABLE_SIZE;
}

// --- Dictionary Operations ---

/**
 * a) Adds a new record (string) to the dictionary using the hash function.
 * This is a simplified dictionary where the key and value are the same string.
 * @param str The string to add to the dictionary.
 */
void add_rec(const string& str) {
    int index = calculate_hash(str);

    // Create the new entry (key = value = str)
    DictionaryEntry* newEntry = new DictionaryEntry;
    newEntry->key = str;
    newEntry->value = str; // Assuming value is the same as the key for simplicity
    newEntry->next = nullptr;

    // Separate Chaining logic
    if (hashTable[index] == nullptr) {
        // No collision: insert at the head
        hashTable[index] = newEntry;
    } else {
        // Collision: Traverse to the end of the chain and insert
        DictionaryEntry* current = hashTable[index];
        
        // Before inserting, check if the word already exists (avoid duplicates)
        while (current != nullptr) {
            if (current->key == str) {
                cout << "Note: Word \"" << str << "\" already exists at index " << index << "." << endl;
                delete newEntry; // Clean up the newly created entry
                return;
            }
            if (current->next == nullptr) {
                break; // Found the end of the chain
            }
            current = current->next;
        }

        current->next = newEntry;
    }

    // Optional confirmation message (used in example)
    // cout << "Added \"" << str << "\" at index " << index << endl;
}

/**
 * b) Searches for a single string in the dictionary.
 * @param str The string key to search for.
 */
void word_search(const string& str) {
    int index = calculate_hash(str);
    DictionaryEntry* current = hashTable[index];

    // Traverse the chain at the calculated index
    while (current != nullptr) {
        if (current->key == str) {
            cout << "search key " << str << ": " << current->value << endl;
            return; // Found the word
        }
        current = current->next;
    }

    // If loop finishes without finding the word
    cout << "Error: Word \"" << str << "\" not found in the dictionary." << endl;
}

/**
 * Optional: Deletes a word from the dictionary.
 * @param str The string key to delete.
 */
void delete_word(const string& str) {
    int index = calculate_hash(str);
    DictionaryEntry* current = hashTable[index];
    DictionaryEntry* prev = nullptr;

    // Traverse the chain
    while (current != nullptr) {
        if (current->key == str) {
            // Found the word
            if (prev == nullptr) {
                // Deleting the head of the list
                hashTable[index] = current->next;
            } else {
                // Deleting a middle or end node
                prev->next = current->next;
            }

            // Free the memory
            delete current;
            cout << "key " << str << " deleted successfully !" << endl;
            return;
        }
        prev = current;
        current = current->next;
    }

    // If loop finishes without finding the word
    cout << "Error: Key \"" << str << "\" not found for deletion." << endl;
}

/**
 * c) Displays the complete dictionary, only showing indices with entries.
 */
void print_dictionary() {
    cout << "\n--- Complete Dictionary Contents ---\n";
    bool dictionary_empty = true;

    for (int i = 0; i < TABLE_SIZE; ++i) {
        DictionaryEntry* current = hashTable[i];
        if (current != nullptr) {
            dictionary_empty = false;
            cout << "index " << i << ": ";
            // Traverse the chain at this index
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

    if (dictionary_empty) {
        cout << "The dictionary is empty." << endl;
    }
    cout << "----------------------------------\n";
}

// Optional: Clean up memory
void cleanup_dictionary() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        DictionaryEntry* current = hashTable[i];
        while (current != nullptr) {
            DictionaryEntry* to_delete = current;
            current = current->next;
            delete to_delete;
        }
        hashTable[i] = nullptr;
    }
}

// --- Main Function with Examples ---

int main() {
    
    add_rec("AB"); 
    add_rec("CD"); 
    add_rec("FASTNU"); 
    add_rec("CS"); 
    add_rec("dA");
    add_rec("EF");
    cout << "\n--- Operation Results ---\n";

    word_search("FASTNU");
    word_search("AB");
    word_search("CS");
    word_search("XYZ"); 

    delete_word("EF");
    delete_word("EF");

    print_dictionary();

    cleanup_dictionary();

    return 0;
}