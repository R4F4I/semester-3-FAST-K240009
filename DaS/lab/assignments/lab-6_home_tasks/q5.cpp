/*

Task 5: Implement a Queue based approach where assume you are the cashier in a supermarket and
you need to make checkouts. Customer ID’s Are 13,7,4,1,6,8,10. (Note: Use Arrays to accomplish this
task with enqueue and dequeue)

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/



#include <iostream>

using namespace std;

/**
 * @class Queue
 * @brief Implements a FIFO (First-In, First-Out) queue using a dynamic
 * array, managed in a circular fashion.
 */
class Queue {
private:
    int* arr;         // Pointer to the dynamic array
    int capacity;    // Maximum number of items the queue can hold
    int front;       // Index of the front element (for dequeue)
    int rear;        // Index of the last element (for enqueue)
    int currentSize; // Current number of elements in the queue

public:
    /**
     * @brief Constructor for the Queue.
     * @param size The maximum capacity of the queue.
     */
    Queue(int size) {
        capacity = size;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        currentSize = 0;
    }

    /**
     * @brief Destructor to clean up the dynamically allocated memory.
     */
    ~Queue() {
        delete[] arr;
    }

    /**
     * @brief Checks if the queue is full.
     */
    bool isFull() {
        return (currentSize == capacity);
    }

    /**
     * @brief Checks if the queue is empty.
     */
    bool isEmpty() {
        return (currentSize == 0);
    }

    /**
     * @brief Adds a customer (ID) to the back of the queue.
     */
    void enqueue(int customerID) {
        if (isFull()) {
            cout << "Queue Full. Cannot add " << customerID << "." << endl;
            return;
        }

        rear = (rear + 1) % capacity;
        arr[rear] = customerID;
        currentSize++;
        
        cout << "Enqueued: " << customerID << endl;
    }

    /**
     * @brief Removes and returns the customer (ID) from the front of the queue.
     */
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Empty." << endl;
            return -1; // Sentinel value
        }

        int customerID = arr[front];
        front = (front + 1) % capacity;
        currentSize--;

        cout << "Dequeued: " << customerID << endl;
        return customerID;
    }

    /**
     * @brief Displays the current state of the queue from front to rear.
     */
    void printQueue() {
        if (isEmpty()) {
            cout << "Queue: [ EMPTY ]" << endl;
            return;
        }

        cout << "Queue: [ ";
        
        int i = front;
        for (int count = 0; count < currentSize; count++) {
            cout << arr[i] << " ";
            i = (i + 1) % capacity;
        }
        cout << "]" << endl;
    }
};

// --- Main Program ---
int main() {
    int customerIDs[] = {13, 7, 4, 1, 6, 8, 10};
    int numCustomers = 7;

    Queue checkoutLine(numCustomers);
    checkoutLine.printQueue();
    cout << endl;

    // Enqueue all customers
    for (int i = 0; i < numCustomers; i++) {
        checkoutLine.enqueue(customerIDs[i]);
        checkoutLine.printQueue();
    }

    cout << "\nEnqueue complete.\n" << endl;

    // Dequeue all customers
    while (!checkoutLine.isEmpty()) {
        checkoutLine.dequeue();
        checkoutLine.printQueue();
    }

    cout << "\nDequeue complete.\n" << endl;
    checkoutLine.printQueue();

    return 0;
}