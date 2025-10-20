#include <iostream>

// ======================================================
//  Class Definitions (as required)
// ======================================================

/**
 * @brief A simple Node class for our linked list (Queue).
 * It holds an integer value and a pointer to the next Node.
 */
class Node {
public:
    int data;
    Node* next;

    // Constructor
    Node(int val) {
        data = val;
        next = nullptr; // Use nullptr for modern C++
    }
};

/**
 * @brief A simple Queue class based on a linked list.
 * It follows the First-In, First-Out (FIFO) principle.
 */
class Queue {
public:
    Node *front, *rear;

    // Constructor
    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    // Destructor to prevent memory leaks
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    /**
     * @brief Checks if the queue is empty.
     * @return true if the queue has no elements, false otherwise.
     */
    bool isEmpty() {
        return front == nullptr;
    }

    /**
     * @brief Adds a new value to the end (rear) of the queue.
     * @param val The integer value to add.
     */
    void enqueue(int val) {
        Node* newNode = new Node(val);
        
        // If the queue is empty, the new node is both front and rear
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            // Otherwise, add it after the current rear
            rear->next = newNode;
            rear = newNode;
        }
    }

    /**
     * @brief Removes and returns the value from the front of the queue.
     * @return The integer value from the front. Returns -1 if empty (for simplicity).
     */
    int dequeue() {
        if (isEmpty()) {
            // In a real-world app, we might throw an exception
            return -1; 
        }

        Node* temp = front;
        int val = temp->data;
        
        // Move the front pointer to the next node
        front = front->next;

        // If the queue is now empty, update the rear pointer as well
        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp; // Free the memory of the removed node
        return val;
    }
};

// ======================================================
//  Radix Sort Implementation
// ======================================================

/**
 * @brief Helper function to find the maximum value in an array.
 * This is needed to know how many digits (passes) to sort by.
 * @param arr The array of integers.
 * @param n The size of the array.
 * @return The largest integer in the array.
 */
int getMax(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

/**
 * @brief Performs a Radix Sort (LSD) on an array of integers using queues.
 * @param arr The array to be sorted (will be modified in-place).
 * @param n The size of the array.
 */
void radixSort(int arr[], int n) {
    // 1. Find the maximum number to know the number of digits
    int maxVal = getMax(arr, n);

    // 2. Create 10 "bins" (queues), one for each digit (0-9)
    // We must use 'new' here if the class has a non-trivial destructor
    // to correctly manage an array of objects.
    Queue* bins = new Queue[10];

    // 3. Loop for every digit place (1s, 10s, 100s, etc.)
    // 'exp' represents the current digit's place (1, 10, 100)
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        
        // --- Distribution Pass ---
        // Place all numbers from the array into their respective bins
        for (int i = 0; i < n; i++) {
            // Get the digit at the current 'exp' place
            int binIndex = (arr[i] / exp) % 10;
            
            // Enqueue the *entire number* into the correct bin
            bins[binIndex].enqueue(arr[i]);
        }

        // --- Collection Pass ---
        // Re-collect the numbers from the bins back into the array
        int arrIndex = 0; // Index to rebuild the original array
        
        // Iterate through all 10 bins in order (0 through 9)
        for (int i = 0; i < 10; i++) {
            // Dequeue all numbers from the current bin
            while (!bins[i].isEmpty()) {
                arr[arrIndex] = bins[i].dequeue();
                arrIndex++;
            }
        }
        // At this point, the array 'arr' is sorted by the current digit place (exp)
    }

    // Clean up the dynamically allocated array of Queues
    delete[] bins;
}

// ======================================================
//  Main Program (Driver Code)
// ======================================================

/**
 * @brief Helper function to print the contents of an array.
 */
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original array: ";
    printArray(arr, n);

    // Perform the sort
    radixSort(arr, n);

    std::cout << "Sorted array:   ";
    printArray(arr, n);

    return 0;
}
