/*

Implement Quick Sort using linked list in C++. Define a node for a linked list with integer data
and a pointer to the next node. Write a function to swap two nodes in the linked list. Write a
function to partition the linked list using the last node as the pivot. Implement the Quick Sort
algorithm using the partition function and the swap function. Finally, write a function to print the
sorted linked list. Your implementation should be able to handle empty linked lists and linked lists
with only one node. Test your implementation with a sample linked list containing the following
integers: 10, 7, 8, 9, 1, 5, 3. The expected output after sorting should be: 1 3 5 7 8 9 10.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

/*
This program implements the Quick Sort algorithm for a singly linked list.
It sorts the list in ascending order using the last node as the pivot.
*/

#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;

    // Constructor to initialize a new node
    Node(int d) {
        data = d;
        next = nullptr;
    }
};


void swap(Node* a, Node* b) {
    // We swap the data, not the nodes themselves,
    // as node swapping in a singly linked list is complex.
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}


Node* getLastNode(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    return temp;
}


Node* partition(Node* start, Node* end) {
    if (start == nullptr || end == nullptr || start == end) {
        return start;
    }
    
    int pivotValue = end->data;
    Node* i = start; // 'i' is the "wall" or "swap target"

    // 'j' is the iterator, from the start to the node *before* the end
    for (Node* j = start; j != end; j = j->next) {
        if (j->data < pivotValue) {
            // Found an element smaller than the pivot.
            // Swap it with the 'i' element.
            swap(i, j);
            
            // Advance the 'i' position
            i = i->next;
        }
    }
    
    // After the loop, 'i' is at the correct final position for the pivot.
    // Swap the pivot (end) into its correct place.
    swap(i, end);
    
    // Return the pivot node
    return i;
}


void quickSortRecursive(Node* start, Node* end) {
    // Base case: 0 or 1 element, or invalid range
    if (start == nullptr || end == nullptr || start == end) {
        return;
    }

    // Partition the list and get the new pivot node
    Node* pivotNode = partition(start, end);

    // --- Recurse on the left partition (start to pivotPrev) ---
    if (pivotNode != start) {
        // We must find the node *before* the pivot to sort the left side
        Node* pivotPrev = start;
        while (pivotPrev != nullptr && pivotPrev->next != pivotNode) {
            pivotPrev = pivotPrev->next;
        }
        
        // Recurse on the left side, from the start to the node *before* the pivot
        quickSortRecursive(start, pivotPrev);
    }
    
    // --- Recurse on the right partition (pivotNext to end) ---
    quickSortRecursive(pivotNode->next, end);
}


void quickSort(Node** head_ref) {
    Node* head = *head_ref;
    
    // Handle empty or single-node lists
    if (head == nullptr || head->next == nullptr) {
        return;
    }
    
    // Find the last node
    Node* last = getLastNode(head);
    
    // Call the recursive helper
    quickSortRecursive(head, last);
}


void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}


void addNode(Node** head_ref, int newData) {
    Node* newNode = new Node(newData);
    if (*head_ref == nullptr) {
        *head_ref = newNode;
        return;
    }
    Node* last = *head_ref;
    while (last->next != nullptr) {
        last = last->next;
    }
    last->next = newNode;
}


int main() {
    Node* head = nullptr;

    // Test with the sample linked list: 10, 7, 8, 9, 1, 5, 3
    addNode(&head, 10);
    addNode(&head, 7);
    addNode(&head, 8);
    addNode(&head, 9);
    addNode(&head, 1);
    addNode(&head, 5);
    addNode(&head, 3);

    cout << "Original linked list: ";
    printList(head);

    // Sort the linked list
    quickSort(&head);

    cout << "Sorted linked list: ";
    printList(head);

    // Clean up memory (optional but good practice)
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}