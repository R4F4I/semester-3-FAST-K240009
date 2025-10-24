/*

Task 7: Consider a library where books are borrowed and returned by multiple patrons. The library
has a limited number of staff members to handle the book transactions. As patrons arrive with books
to borrow or return, they are added to a linear queue. Each book transaction can take a variable amount
of time to complete, depending on factors such as the number of books being borrowed or returned,
and the availability of the staff members. Once a book transaction is completed, the next patron in the
queue is serviced.
Write a C++ program that simulates this library scenario using a linear queue data structure. The
program should allow patrons to add themselves to the queue, remove themselves from the queue
when their book transaction is completed, and display the current queue of patrons waiting for book
transactions to be serviced.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

// A circular queue for the library line
class Queue {
private:
    int* arr;
    int capacity;
    int front, rear, currentSize;

public:
    // Constructor: makes the dynamic array for the line
    Queue(int size) {
        if (size <= 0) size = 10; // Just in case
        capacity = size;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        currentSize = 0;
    }

    // Destructor: cleans up the memory
    ~Queue() {
        delete[] arr;
    }

    // --- Required Functions ---

    
    //   Adds a patron (by ID) to the end of the line.
    
    void addPatron(int patronID) {
        if (currentSize == capacity) {
            cout << "Line is full. Patron " << patronID << " has to wait." << endl;
            return;
        }

        rear = (rear + 1) % capacity;
        arr[rear] = patronID;
        currentSize++;
        cout << "Patron " << patronID << " in line." << endl;
    }

    
    //   Services the patron at the front of the line.
    //   Returns the ID of the patron, or -1 if the line is empty.
    
    int servicePatron() {
        if (currentSize == 0) {
            cout << "Line is empty. No one to service." << endl;
            return -1;
        }

        int servicedPatron = arr[front];
        front = (front + 1) % capacity;
        currentSize--;
        
        cout << "Servicing patron " << servicedPatron << "." << endl;
        return servicedPatron;
    }

    /**
     * Displays the current line of patrons.
     */
    void displayLine() {
        if (currentSize == 0) {
            cout << "Line: [ EMPTY ]" << endl;
            return;
        }

        cout << "Line (Front to Back): [ ";
        int i = front;
        for (int count = 0; count < currentSize; count++) {
            cout << arr[i] << " ";
            i = (i + 1) % capacity;
        }
        cout << "]" << endl;
    }
};

// --- Main Simulation ---
int main() {
    // Make a line that can hold 5 people
    Queue libraryLine(5);

    // Show the empty line
    libraryLine.displayLine();

    // Patrons 101, 102, 103 arrive
    libraryLine.addPatron(101);
    libraryLine.addPatron(102);
    libraryLine.addPatron(103);
    libraryLine.displayLine();

    // Service one patron
    libraryLine.servicePatron();
    libraryLine.displayLine();

    // More patrons arrive
    libraryLine.addPatron(104);
    libraryLine.addPatron(105);
    libraryLine.addPatron(106); // Line is now full
    libraryLine.displayLine();

    // Patron 107 tries to join the full line
    libraryLine.addPatron(107);
    libraryLine.displayLine();

    // Service everyone else
    cout << "\n--- Servicing the rest of the line ---" << endl;
    libraryLine.servicePatron();
    libraryLine.servicePatron();
    libraryLine.servicePatron();
    libraryLine.servicePatron();
    libraryLine.displayLine();

    // Try to service an empty line
    libraryLine.servicePatron();

    return 0;
}