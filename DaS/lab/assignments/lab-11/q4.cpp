/*

Given an array of distinct integers, find using hashing if there are two pairs (a, b) and (c, d) such that
a+b = c+d, and a, b, c, and d are distinct elements. If there are multiple answers, then print any of
them.
Input: {3, 4, 7, 1, 2, 9, 8}
Output: (3, 8) and (4, 7)
Explanation: 3+8 = 4+7
Input: {3, 4, 7, 1, 12, 9};
Output: (4, 12) and (7, 9)
Explanation: 4+12 = 7+9
Input: {65, 30, 7, 90, 1, 9, 8};
Output: No pairs found


*/
#include <iostream>
#define TABLE_SIZE 1000

using namespace std;

// Data Structures for Hash Map

// 1. Structure to store the pair of elements {a, b}
struct Pair {
    int first;
    int second;
};

// 2. Structure for the Hash Table Node
struct HashNode {
    int sum;         // Key of the hash map
    Pair p;          // Value of the hash map (the pair that produced the sum)
    HashNode* next;  // For Separate Chaining
};

// Hash Table Operations

// Define a size for the hash table array
HashNode* hashTable[TABLE_SIZE] = {nullptr}; // The hash table array

/**
 * Calculates the hash index for a given sum.
 * Hash Function: sum MOD TABLE_SIZE
 */
int calculate_hash(int sum) {
    // A simple modulo operation works for non-negative sums
    return sum % TABLE_SIZE;
}

/**
 * Tries to insert a sum/pair into the hash table.
 * If the sum already exists, it checks for the solution.
  'currentSum' The sum of the current pair (c, d).
  'currentPair' The pair {c, d}.
  'a' The first element of the current pair.
  'b' The second element of the current pair.
  'True' if a solution is found, false otherwise.
 */
bool insert_and_check(int currentSum, Pair currentPair) {
    int index = calculate_hash(currentSum);
    HashNode* current = hashTable[index];

    // Traverse the chain at the calculated index
    while (current != nullptr) {
        if (current->sum == currentSum) {
            // Sum already exists! We found a potential match: a+b = c+d
            
            // Check if all four elements (a, b) and (c, d) are distinct
            int a = current->p.first;
            int b = current->p.second;
            int c = currentPair.first;
            int d = currentPair.second;
            
            // The problem guarantees the input array has distinct integers, 
            // so we only need to check if the new elements (c, d) conflict with the old ones (a, b)
            if (a != c && a != d && b != c && b != d) {
                // SOLUTION FOUND!
                cout << "Output: (" << a << ", " << b << ") and (" << c << ", " << d << ")" << endl;
                cout << "Explanation: " << a << "+" << b << " = " << c << "+" << d << " = " << currentSum << endl;
                return true;
            }
            // If the pairs share an element (e.g., a+b = a+d), continue checking the chain 
            // or just ignore this entry and proceed, as this entry does not give a distinct solution.
        }
        current = current->next;
    }

    // Sum not found or no distinct solution found in the chain. Insert the new pair.
    HashNode* newNode = new HashNode;
    newNode->sum = currentSum;
    newNode->p = currentPair;

    // Insert at the head (Separate Chaining)
    newNode->next = hashTable[index];
    hashTable[index] = newNode;

    return false; // No solution found yet
}

/**
 * Main logic function to find the required pairs.
 * @param arr The array of distinct integers.
 * @param size The size of the array.
 */
void find_pairs(int arr[], int size) {
    
    // Iterate over all possible pairs (i, j) where i < j
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            
            int currentSum = arr[i] + arr[j];
            Pair currentPair = {arr[i], arr[j]};
            
            // Check the hash map for an existing sum
            if (insert_and_check(currentSum, currentPair)) {
                // If a solution is found, stop and return
                return;
            }
        }
    }

    // If the loops complete without finding a solution
    cout << "Output: No pairs found" << endl;
}

/**
 * Clean up the dynamically allocated hash table memory.
 */
void cleanup_hash_table() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashNode* current = hashTable[i];
        while (current != nullptr) {
            HashNode* to_delete = current;
            current = current->next;
            delete to_delete;
        }
        hashTable[i] = nullptr;
    }
}

// Main Execution

int main() {
    
    // Example 1
    int arr1[] = {3, 4, 7, 1, 2, 9, 8};
    int size1 = sizeof(arr1)/sizeof(arr1[0]); // 7
    cout << "Input: {3, 4, 7, 1, 2, 9, 8}" << endl;
    find_pairs(arr1, size1);
    cleanup_hash_table();
    cout << endl;

    // Example 2
    int arr2[] = {3, 4, 7, 1, 12, 9};
    int size2 = sizeof(arr2)/sizeof(arr2[0]) ; //6;
    cout << "Input: {3, 4, 7, 1, 12, 9}" << endl;
    find_pairs(arr2, size2);
    cleanup_hash_table();
    cout << endl;
    
    // Example 3
    int arr3[] = {65, 30, 7, 90, 1, 9, 8};
    int size3 = sizeof(arr3)/sizeof(arr3[0]); // 7;
    cout << "Input: {65, 30, 7, 90, 1, 9, 8}" << endl;
    find_pairs(arr3, size3);
    cleanup_hash_table();
    cout << endl;

    return 0;
}