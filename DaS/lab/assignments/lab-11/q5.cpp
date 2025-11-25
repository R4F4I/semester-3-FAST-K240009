/*

Implement a C++ class StudentHashTable to manage student records in a hash table with a size of 15. Use
quadratic probing for collision resolution with the formula (index + attempt^2) % table size.Implement the
function InsertRecord that takes a student's roll number and name, inserting the record into the hash table
using quadratic probing.Implement the function SearchRecord that takes a roll number, searches for the
corresponding record using quadratic probing, and prints the student's name if found; otherwise, print a
"Record not found" message.


*/
#include <iostream>
#define TABLE_SIZE 15


using namespace std;


// Structure to hold student data
struct StudentRecord {
    int rollNumber;
    string name;
    // Status to track if the slot is occupied (needed for probing)
    bool isOccupied; 
};

// Hash Table Class

class StudentHashTable {
public:
    StudentRecord table[TABLE_SIZE]; // Fixed-size array for the hash table

    // Constructor to initialize the table
    StudentHashTable() {
        // Mark all slots as unoccupied initially
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i].isOccupied = false;
            table[i].rollNumber = -1; // Use -1 to denote an empty roll number
        }
    }

    /**
     * Calculates the initial hash index using modulo division.
     * @param roll The student roll number.
     * @return The base hash index (0 to 14).
     */
    int hashFunction(int roll) {
        return roll % TABLE_SIZE;
    }

    // 1. Insert Record Function
    void InsertRecord(int roll, const string& studentName) {
        int baseIndex = hashFunction(roll);
        
        // Quadratic Probing loop
        for (int attempt = 0; attempt < TABLE_SIZE; ++attempt) {
            // Formula: (baseIndex + attempt^2) % TABLE_SIZE
            int index = (baseIndex + attempt * attempt) % TABLE_SIZE;

            if (!table[index].isOccupied) {
                // Found an empty slot, insert the record
                table[index].rollNumber = roll;
                table[index].name = studentName;
                table[index].isOccupied = true;
                cout << "Record inserted for " << studentName << " (Roll " << roll << ") at index " << index << endl;
                return;
            }

            // Optional: Handle case where the roll number is already present (update/ignore)
            if (table[index].rollNumber == roll) {
                cout << "Error: Roll number " << roll << " already exists." << endl;
                return;
            }
        }
        
        // If the loop finishes, the table is full or probing failed (very rare for prime size)
        cout << "Error: Hash table is full. Failed to insert roll " << roll << endl;
    }

    // 2. Search Record Function
    void SearchRecord(int roll) {
        int baseIndex = hashFunction(roll);
        
        // Quadratic Probing loop (must use the same probing sequence as insert)
        for (int attempt = 0; attempt < TABLE_SIZE; ++attempt) {
            // Formula: (baseIndex + attempt^2) % TABLE_SIZE
            int index = (baseIndex + attempt * attempt) % TABLE_SIZE;

            if (table[index].rollNumber == roll && table[index].isOccupied) {
                // Found the record
                cout << "Search successful: Roll " << roll << " belongs to " << table[index].name << endl;
                return;
            }
            
            // Critical optimization: If we hit a truly empty slot (never used), 
            // the record can't be found past this point.
            if (!table[index].isOccupied && table[index].rollNumber == -1) {
                break; 
            }
            // Note: If using "soft deletion," this optimization is not possible.
        }

        // If the loop finishes or breaks early
        cout << "Record not found for roll number " << roll << endl;
    }
    
    // Optional: Display function to see the table state
    void DisplayTable() {
        cout << "\nTable Status:\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << i << ": ";
            if (table[i].isOccupied) {
                cout << "(" << table[i].rollNumber << ", " << table[i].name << ")";
            } else {
                cout << "Empty";
            }
            cout << endl;
        }
    }
};

// Main Function with Hardcoded Examples

int main() {
    
    StudentHashTable myTable;

    // Roll numbers and their hash indices (mod 15):
    // 30 -> 0
    // 15 -> 0 (Collision 1)
    // 31 -> 1
    // 16 -> 1 (Collision 2)
    // 50 -> 5
    // 20 -> 5 (Collision 3)
    
    // 1. Insert Examples
    cout <<  "Insertion Test\n";
    myTable.InsertRecord(30, "Alice"); // Base 0 -> Insert at 0
    myTable.InsertRecord(31, "Bob");   // Base 1 -> Insert at 1
    myTable.InsertRecord(50, "Charlie"); // Base 5 -> Insert at 5

    // Collision 1: Roll 15 (Base 0)
    // attempt 0: (0 + 0^2) % 15 = 0 (Occupied by Alice)
    // attempt 1: (0 + 1^2) % 15 = 1 (Occupied by Bob)
    // attempt 2: (0 + 2^2) % 15 = 4 (Empty) -> Insert at 4
    myTable.InsertRecord(15, "David"); 
    
    // Collision 2: Roll 16 (Base 1)
    // attempt 0: (1 + 0^2) % 15 = 1 (Occupied by Bob)
    // attempt 1: (1 + 1^2) % 15 = 2 (Empty) -> Insert at 2
    myTable.InsertRecord(16, "Eve");

    // Collision 3: Roll 20 (Base 5)
    // attempt 0: (5 + 0^2) % 15 = 5 (Occupied by Charlie)
    // attempt 1: (5 + 1^2) % 15 = 6 (Empty) -> Insert at 6
    myTable.InsertRecord(20, "Frank");

    // myTable.DisplayTable(); // Optional display

    // 2. Search Examples
    cout <<"Search Test\n";
    
    // Search for non-collided record
    myTable.SearchRecord(30); 
    
    // Search for a collided record (David, at index 4)
    myTable.SearchRecord(15); 
    
    // Search for another collided record (Frank, at index 6)
    myTable.SearchRecord(20);
    
    // Search for a non-existent record
    myTable.SearchRecord(99); 

    return 0;
}