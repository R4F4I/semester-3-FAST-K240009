/*

Task#7:
Create a circular link list and perform the mentioned tasks.
a. Insert a new node at the end of the list.
b. Insert a new node at the beginning of list.
c. Insert a new node at given position.
d. Delete any node.
e. Print the complete circular link list.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;


class Node
{
public:
    int data;
    Node *next;

    // constructor
    Node(int data){
        this->data = data;
        next = nullptr;
    }
    Node(){
        this->data = 0;
        next = nullptr;
    }
};
class circ_LL
{
public:
    Node *head, *tail;
    int length;
    circ_LL(){
        head = nullptr;
        tail = nullptr;
    }


    // same as singly LL, except last node will point to the new node
    void insert_start(int data){
        
        Node *new_node = new Node(data);
        
        // empty LL checker
        if (head == nullptr) // the value of head ptr
        {
            head = new_node;
            return;
        } else {
            new_node->next = head; // copy the value of head / new_node is pointing where is head is pointing
            head = new_node; // head now points to the new node
            tail->next = new_node; // last node points to the new node as well
            return;
        }
    }


    // insert a data at the end of the node
    void insert_end(int data){
        // allocate memory (using new) of size node, return type pointer of node, why? to prevent the local var from being destroyed when the function ends (DMA prevents the var from being destroyed automatically) 
        // also new_node is pointer to this DMA created node, it contains the node's address not its value
        Node *new_node = new Node(data);
        
        // empty LL checker
        if (head == nullptr) // the value of head ptr
        {
            head = new_node; // copy the new_nodes address into head
            tail = new_node;
            return;
        }

        // since tail is pointing to last node, just use it instead of traversal
        tail->next = new_node;
        // tail points to the new node
        tail = new_node;
        // since this is a circ ll, the last node will point to first node
        new_node->next = head;

    }


    // delete the first node (conserve memory)
    void remove_start(){
        
        Node *temp = head; // temp will point to first node
        
        // the head will simply point to the next node
        head = head->next;

        // the last node will point to this next node
        tail->next = head;
        
        delete temp; // deleting the dangling node
    }


    // 2nd last node will simply point to first node
    void remove_end(){
        if (head!=nullptr)
        {
            Node *prev=nullptr, *next=head;
            // traverse to end with 2 pointers
            while (next!=tail) // check whether the next pointer is pointing to the last node
            {
                prev = next;
                next = next->next;
            }
            prev->next = head;
            tail = prev;
            // this will leave a dangling node

            delete next; // deleting the dangling node
        }
    }

    // remove node at nth position
    void remove_pos(int pos){
        if(pos == 1){
            remove_start();
            return;
        }
        if (head!=nullptr)
        {
            Node *prev = nullptr, *curr = nullptr, *next = head;
            while (pos-- != 0)
            {
                prev = curr;
                curr = next;
                next = next->next;
            }
            // get the prev node to point to next node, leaving the middle node dangling

            prev->next = next;

            // delete the dangling node

            delete curr;
        }
    }


    // will point until the node at which tail is pointing is reached
    void print(){
        Node *temp = head; // a temporary pointer to traverse through the LL
        
        do
        {
            std::cout << temp->data << " -> ";
            // std::cout << "\" "<< temp->data << "  " << head->data << " \"";
            temp = temp->next;
        }
        while (temp!=head); // traverse until it circles back
        std::cout <<"head"<< std::endl;
        
    }
};



int main(){

    circ_LL ll;

    ll.insert_end(2);
    ll.insert_end(3);
    ll.insert_end(4);
    ll.print();
    ll.insert_end(5);
    ll.print();
    ll.insert_start(6);
    ll.insert_start(7);
    ll.insert_start(8);
    ll.insert_start(9);
    ll.print();

    ll.remove_pos(3);
    ll.print();
    ll.remove_end();
    ll.print();
    ll.remove_start();
    ll.print();




    return 0;
}