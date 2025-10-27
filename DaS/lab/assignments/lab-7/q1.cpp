/* 

Task-1:
Suppose you are given a list of student records, where each record contains a student&#39;s name and
their score on a recent test. You need to sort this list by score in ascending order using Radix Sort,
and represent the list using a linked list in C++.

Design and implement a Radix Sort algorithm using a linked list to sort the student records.
Assume that each student&#39;s score is an integer between 0 and 100, and that there are no more than
10,000 students in the list. After that asks the user to enter the name and score if that record is
available in the list, then delete that record and display the updated list. Otherwise do nothing. Note
use binary search to search the record in the linked list.

Input :

addNode(&amp;head, “Ayan” , 90);
addNode(&amp;head, “Zameer” , 60);
addNode(&amp;head, “Sara” , 70);
addNode(&amp;head, “Sohail” , 30);
addNode(&amp;head, “Ahmed” , 20);

Output:

Ahmed 20
Sohail 30
Zameer 60
Sara 70
Ayan 90


*/


#include <iostream>
using namespace std;


/**
 * Represents a node in the doubly linked list.
 * Stores a student's name and score.
 */
class Node {
public:
    string name;
    int data; // Represents the student's score
    Node *next, *prev;

    /**
     * Constructor for Node.
     * n Student's name.
     * d Student's score.
     */
    Node(string n, int d) {
        this->name = n;
        this->data = d;
        next = nullptr;
        prev = nullptr;
    }
};

/**
 * A simple Queue implementation using a doubly linked list.
 * Used for the "bins" in Radix Sort.
 */
class Queue {
public:
    Node *head, *tail;

    Queue() {
        head = nullptr;
        tail = nullptr;
    }

    /**
     * Adds a node to the end (tail) of the queue.
     * node The node to enqueue.
     */
    void Enq(Node* node) {
        // Ensure the node is detached
        node->next = nullptr;
        node->prev = nullptr;

        if (tail == nullptr) { // Queue is empty
            head = node;
            tail = node;
        } else { // Add to the end
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    /**
     * Removes and returns the node from the front (head) of the queue.
     * The dequeued node, or nullptr if the queue is empty.
     */
    Node* Deq() {
        if (head == nullptr) { // Queue is empty
            return nullptr;
        }

        Node* temp = head;
        head = head->next;

        if (head != nullptr) {
            head->prev = nullptr;
        } else { // Queue is now empty
            tail = nullptr;
        }

        // Detach the node completely
        temp->next = nullptr;
        temp->prev = nullptr;
        return temp;
    }

    /**
     * Checks if the queue is empty.
     * true if the queue is empty, false otherwise.
     */
    bool isEmpty() {
        return head == nullptr;
    }
};

/**
 * Adds a new student record to the end of the linked list.
 * head_ref A pointer to the head pointer of the list.
 * name The student's name.
 * data The student's score.
 */
void addNode(Node** head_ref, string name, int data) {
    Node* newNode = new Node(name, data);

    if (*head_ref == nullptr) { // List is empty
        *head_ref = newNode;
        return;
    }

    // Traverse to the end of the list
    Node* last = *head_ref;
    while (last->next != nullptr) {
        last = last->next;
    }

    // Link the new node
    last->next = newNode;
    newNode->prev = last;
}

/**
 * Prints the entire linked list.
 * head The head node of the list.
 */
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->name << " " << temp->data << endl;
        temp = temp->next;
    }
}

/**
 * Safely deletes a given node from the doubly linked list.
 * head_ref A pointer to the head pointer of the list.
 * del The node to be deleted.
 */
void deleteNode(Node** head_ref, Node* del) {
    if (*head_ref == nullptr || del == nullptr) {
        return;
    }

    // If node to be deleted is head node
    if (*head_ref == del) {
        *head_ref = del->next;
    }

    // Change next only if node to be deleted is NOT the last node
    if (del->next != nullptr) {
        del->next->prev = del->prev;
    }

    // Change prev only if node to be deleted is NOT the first node
    if (del->prev != nullptr) {
        del->prev->next = del->next;
    }

    // Free the memory
    delete del;
}

/**
 * Gets the k-th digit (from the right) of a number.
 * number The number to extract the digit from.
 * k The digit position (0 = units, 1 = tens, etc.).
 * The k-th digit.
 */
int NthDigit(int number, int k) {
    int div = 1;
    for (size_t i = 0; i < k; i++) {
        div *= 10;
    }
    return (number / div) % 10;
}

/**
 * Sorts a doubly linked list using Radix Sort (LSD).
 * Assumes scores are between 0 and 100 (max 3 digits).
 * head_ref A pointer to the head pointer of the list.
 */
void radixSort(Node** head_ref) {
    Queue bins[10]; // 10 bins for digits 0-9
    int maxDigits = 3; // For scores 0-100

    for (int k = 0; k < maxDigits; k++) {
        // --- Distribution Pass ---
        // Move all nodes from the main list into the bins
        Node* current = *head_ref;
        while (current != nullptr) {
            Node* nextNode = current->next; // Save the next node
            int digit = NthDigit(current->data, k);
            bins[digit].Enq(current); // Enqueues the node, detaching it
            current = nextNode;
        }
        *head_ref = nullptr; // Main list is now empty

        // --- Collection Pass ---
        // Rebuild the list from the bins
        Node* newTail = nullptr;
        for (int i = 0; i < 10; i++) {
            while (!bins[i].isEmpty()) {
                Node* node = bins[i].Deq();

                if (*head_ref == nullptr) { // First node being added
                    *head_ref = node;
                    newTail = node;
                } else { // Append to the end
                    newTail->next = node;
                    node->prev = newTail;
                    newTail = node;
                }
            }
        }
    }
}

/**
 * Finds the middle node of a sub-list (from start to end).
 * 'end' is exclusive (one-past-the-last-node).
 * start The starting node of the sub-list.
 * end The (exclusive) end marker of the sub-list.
 * A pointer to the middle node.
 */
Node* getMiddle(Node* start, Node* end) {
    if (start == nullptr) {
        return nullptr;
    }
    Node* slow = start;
    Node* fast = start->next;

    // Move fast two steps, slow one step
    while (fast != end) {
        fast = fast->next;
        if (fast != end) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    return slow;
}

/**
 * Performs a binary search on a sorted doubly linked list.
 * Note: This is inefficient (O(N log N)) but adheres to the prompt.
 * It first finds a node with the matching score, then scans
 * linearly for the matching name.
 * head The head of the sorted list.
 * name The name to search for.
 * score The score to search for.
 * A pointer to the node if found, otherwise nullptr.
 */
Node* binarySearch(Node* head, string name, int score) {
    Node* start = head;
    Node* end = nullptr; // 'end' is one past the last node

    while (start != end) {
        Node* mid = getMiddle(start, end);

        if (mid == nullptr) {
            return nullptr; // List is empty or sub-list is empty
        }

        if (mid->data == score) {
            // Found a matching score. Now find the matching name.
            // Scan left from mid (inclusive)
            Node* temp = mid;
            while (temp != nullptr && temp->data == score) {
                if (temp->name == name) {
                    return temp;
                }
                temp = temp->prev;
            }

            // Scan right from mid (exclusive, since mid was checked)
            temp = mid->next;
            while (temp != nullptr && temp->data == score) {
                if (temp->name == name) {
                    return temp;
                }
                temp = temp->next;
            }
            
            // Score was found, but name was not
            return nullptr;

        } else if (mid->data < score) {
            start = mid->next; // Search in the right half
        } else {
            end = mid; // Search in the left half (end is exclusive)
        }
    }
    
    // Not found
    return nullptr;
}


int main() {
    Node* head = nullptr;

    // Input data
    addNode(&head, "Ayan", 90);
    addNode(&head, "Zameer", 60);
    addNode(&head, "Sara", 70);
    addNode(&head, "Sohail", 30);
    addNode(&head, "Ahmed", 20);

    // Sort the list
    radixSort(&head);

    cout << "Sorted list:" << endl;
    printList(head);
    cout << "---------------------" << endl;

    // --- Search and Delete ---
    string searchName;
    int searchScore;

    cout << "Enter name to delete: ";
    cin >> searchName;
    cout << "Enter score to delete: ";
    cin >> searchScore;

    // Perform binary search on the linked list
    Node* foundNode = binarySearch(head, searchName, searchScore);

    // Delete the node if it was found
    if (foundNode != nullptr) {
        cout << "Record found. Deleting " << foundNode->name << "..." << endl;
        deleteNode(&head, foundNode);
        cout << "Updated list:" << endl;
        printList(head);
    } else {
        cout << "Record not found." << endl;
    }

    // Clean up remaining nodes (optional, good practice)
    while(head != nullptr) {
        deleteNode(&head, head);
    }

    return 0;
}
