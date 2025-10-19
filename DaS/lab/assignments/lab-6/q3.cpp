/*

3: As a software developer, you have been assigned the task of developing an application for a
busy restaurant that can handle a large volume of orders. To ensure that orders are processed in the
order they were received, what type of data structure would you choose to store the orders? Please
describe the necessary operations that would be required to add and remove orders from this data
structure, including the quantity of each item. Additionally, how would you prevent the data structure
from becoming full or empty to avoid overflow or underflow? Finally, explain your approach for
printing out all the processed orders in the order they were received to ensure that the restaurant staff
can efficiently fulfill the orders.

/*

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A

*/

#include <iostream>
#include <string>

using namespace std;

/*
-------------------------------------------------------------------------------------------------
|                                   EXPLANATION OF THE APPROACH                                 |
-------------------------------------------------------------------------------------------------

    What type of data structure would you choose to store the orders?

    The best data structure for managing restaurant orders is a **Queue**. A queue follows the
    **First-In, First-Out (FIFO)** principle. This means the first order received is the first one
    to be processed, which perfectly models a fair and efficient system for a busy restaurant.
    I will implement this queue using a **Linked List** because a restaurant's order volume is
    unpredictable. A linked list allows the queue to grow and shrink dynamically as needed,
    unlike a fixed-size array which could lead to overflow.

    Describe the necessary operations to add and remove orders.

    The two primary operations for a queue are:
    1.  **Enqueue (Add Order):** This operation adds a new order to the *back* (or rear) of the
        queue. When a customer places an order, we `enqueue` it.
    2.  **Dequeue (Process/Remove Order):** This operation removes an order from the *front* of the
        queue. When the kitchen is ready for the next order, they `dequeue` it.

    Each order will also contain a linked list of items (e.g., Pizza, Coke) with their quantities.

    How would you prevent the data structure from becoming full or empty?


    * **Preventing Overflow (Full):** By using a linked list, we effectively prevent overflow.
        The queue can grow as long as there is available system memory (RAM). We don't have a
        pre-defined limit. The only time this would fail is if the entire system runs out of memory,
        which is an extreme and rare system-level error.

    * **Preventing Underflow (Empty):** Underflow happens when we try to `dequeue` an order from an
        empty queue. We prevent this by implementing a check. Before every `dequeue` operation,
        we will call a helper function, `isEmpty()`. If the queue is empty, the `dequeue`
        operation will be stopped, an error message will be displayed, and no processing will occur.
        This prevents the program from crashing by trying to access a non-existent order.

    Explain your approach for printing all the processed orders in the order they were received.

    When an order is processed, it is `dequeue`'d from the main "pending orders" queue. To keep a
    record, we need a second data structure to act as a historical log. I will create a simple
    "OrderHistory" linked list. Every time an order is successfully dequeued, it will be added to
    the end of this history list.

    To print the report, we will simply traverse the `OrderHistory` list from head to tail. Since
    orders were added to this list in the same sequence they were completed, printing it will
    naturally display all processed orders in the correct chronological order.

*/


//--------------------------------------------------------------------
// 1. DATA STRUCTURES DEFINITION
//--------------------------------------------------------------------

// Represents a single item within an order (e.g., "Pizza", quantity: 2)
// An order can have multiple items, so this is a node for a linked list of items.
struct OrderItem {
    string itemName;
    int quantity;
    OrderItem* next; // Pointer to the next item in the same order
};

// Represents a complete customer order, which contains a unique ID and a list of items.
struct Order {
    int orderID;
    OrderItem* itemsHead; // Head of the linked list of items for this order
};

// This is the Node for our Queue's main linked list. Each node holds one complete order.
struct Node {
    Order data;
    Node* next;
};


//--------------------------------------------------------------------
// 2. ORDER QUEUE IMPLEMENTATION
//--------------------------------------------------------------------

class OrderQueue {
private:
    Node* front; // Points to the front of the queue (the next order to be processed)
    Node* rear;  // Points to the back of the queue (where new orders are added)
    int nextOrderID; // A counter to assign unique IDs to new orders

public:
    // Constructor: Initializes an empty queue.
    OrderQueue() {
        front = nullptr;
        rear = nullptr;
        nextOrderID = 1;
    }

    // Destructor: Cleans up all nodes in the queue to prevent memory leaks
    // when the queue object goes out of scope.
    ~OrderQueue() {
        while (!isEmpty()) {
            dequeue(); // Dequeue all elements to free their memory
        }
    }

    // Checks if the queue is empty. This is the core of underflow prevention.
    bool isEmpty() {
        return front == nullptr;
    }

    // OPERATION 1: Add an order (enqueue) to the back of the queue.
    void enqueue(Order newOrder) {
        // Assign a unique, auto-incrementing ID to the incoming order.
        newOrder.orderID = nextOrderID++;
        
        // Create a new node to hold this order.
        Node* newNode = new Node();
        newNode->data = newOrder;
        newNode->next = nullptr;

        // If the queue is empty, the new node is both the front and the rear.
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            // Otherwise, link the current rear node to the new node...
            rear->next = newNode;
            // ...and update the rear to be the new node.
            rear = newNode;
        }
        cout << "Order #" << newOrder.orderID << " has been added to the queue." << endl;
    }

    // OPERATION 2: Remove an order (dequeue) from the front of the queue.
    Order dequeue() {
        // --- UNDERFLOW PREVENTION ---
        // Before trying to remove an order, check if one exists.
        if (isEmpty()) {
            cout << "Underflow Error: No pending orders to process." << endl;
            // Return a default/error order object to signify failure.
            return Order{-1, nullptr}; 
        }

        // Store the node at the front so we can delete it later.
        Node* temp = front;
        Order processedOrder = temp->data;

        // Move the front pointer to the next order in the queue.
        front = front->next;

        // If the queue becomes empty after this dequeue, the rear must also be set to null.
        if (front == nullptr) {
            rear = nullptr;
        }

        // Free the memory of the node that was just processed.
        delete temp;
        return processedOrder;
    }
};


//--------------------------------------------------------------------
// 3. ORDER HISTORY LIST IMPLEMENTATION
//--------------------------------------------------------------------

// This class will store processed orders to maintain a historical record.
// It's a simple linked list that only adds to the end.
class OrderHistory {
private:
    Node* head; // Start of the history list
    Node* tail; // End of the history list (for efficient adding)

public:
    OrderHistory() : head(nullptr), tail(nullptr) {}

    // Destructor to clean up all stored historical orders and their items.
    ~OrderHistory() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            
            // Also delete the linked list of items within each order
            OrderItem* currentItem = current->data.itemsHead;
            while(currentItem != nullptr) {
                OrderItem* nextItem = currentItem->next;
                delete currentItem;
                currentItem = nextItem;
            }
            
            delete current; // Delete the order node itself
            current = nextNode;
        }
    }

    // Adds a processed order to the end of the history list.
    void addProcessedOrder(Order order) {
        Node* newNode = new Node{order, nullptr};
        if (head == nullptr) {
            head = tail = newNode; // If list is empty, it's the first node
        } else {
            tail->next = newNode; // Link the last node to the new one
            tail = newNode;       // Update the tail
        }
    }

    // Prints all orders in the history from start to finish.
    void printAllProcessedOrders() {
        cout << "\n--- Final Report: All Processed Orders ---" << endl;
        if (head == nullptr) {
            cout << "No orders were processed." << endl;
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            cout << "----------------------------------------" << endl;
            cout << "Order ID: " << current->data.orderID << endl;
            OrderItem* currentItem = current->data.itemsHead;
            while (currentItem != nullptr) {
                cout << "  - Item: " << currentItem->itemName 
                     << ", Quantity: " << currentItem->quantity << endl;
                currentItem = currentItem->next;
            }
            current = current->next;
        }
        cout << "----------------------------------------" << endl;
    }
};


int main() {
    // The main queue for incoming orders that need to be processed.
    OrderQueue pendingOrders;

    // The list that will store orders after they have been processed.
    OrderHistory completedOrders;

    // --- STEP 1: Simulate customers placing new orders (ENQUEUE) ---
    cout << "--- Restaurant is Open: New Orders Arriving ---" << endl;
    
    // Create Order 1 with two items
    Order order1;
    order1.itemsHead = new OrderItem{"Margherita Pizza", 1, nullptr};
    order1.itemsHead->next = new OrderItem{"Coke", 2, nullptr}; 
    pendingOrders.enqueue(order1);

    // Create Order 2 with one item
    Order order2;
    order2.itemsHead = new OrderItem{"Chicken Burger", 2, nullptr};
    pendingOrders.enqueue(order2);

    // Create Order 3 with one item
    Order order3;
    order3.itemsHead = new OrderItem{"Pasta Alfredo", 1, nullptr};
    pendingOrders.enqueue(order3);

    // --- STEP 2: Simulate kitchen staff processing orders (DEQUEUE) ---
    cout << "\n--- Kitchen Staff Processing Orders ---" << endl;
    
    // Process the first order (Order #1)
    Order processed1 = pendingOrders.dequeue();
    if (processed1.orderID != -1) { // Check if dequeue was successful
        cout << "Processing Order #" << processed1.orderID << "..." << endl;
        completedOrders.addProcessedOrder(processed1); // Add to history
    }

    // Process the second order (Order #2)
    Order processed2 = pendingOrders.dequeue();
    if (processed2.orderID != -1) {
        cout << "Processing Order #" << processed2.orderID << "..." << endl;
        completedOrders.addProcessedOrder(processed2);
    }
    
    // --- STEP 3: Demonstrate Underflow Prevention ---
    // Let's say we process all remaining orders
    cout << "\n--- Processing Final Pending Order ---" << endl;
    Order processed3 = pendingOrders.dequeue();
     if (processed3.orderID != -1) {
        cout << "Processing Order #" << processed3.orderID << "..." << endl;
        completedOrders.addProcessedOrder(processed3);
    }

    cout << "\n--- Checking for more orders (will trigger underflow) ---" << endl;
    pendingOrders.dequeue(); // Attempt to dequeue from an empty queue

    // --- STEP 4: Print the final report of all processed orders ---
    // This demonstrates the history tracking.
    completedOrders.printAllProcessedOrders();

    return 0;
}