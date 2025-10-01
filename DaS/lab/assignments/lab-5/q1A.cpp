/*

Task-1:
a.
Insert the element at the end of linked list and display the list in reverse direction using Recursion
Approach?
b. Insert the node in doubly linked list at any position, and display the nodes after that delete the node
at any position and again display the updated list.
c.
consider the below maze , start from 0, 0 and target is to reach at (2, 0). Write a back trakng code in
c++ to achieve this. Note that 1 is open and 0 is blocked.
Maze
1 1 1 1
0 0 0 1
1 1 0 1
1 1 1 1

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
    Node *next, *prev;

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
class LL
{
public:
    Node* head;
    LL(){
        head = nullptr;
    }

    

    void insert_end(Node* node){
        // Node *new_node = new Node(data);
        if (head == nullptr) 
        {
            head = node; 
            return;
        }
        Node *temp = head; 
        while (temp->next!=nullptr)
        {
            temp = temp->next;
        }
        temp->next = node;
    }


    void print(Node* head){
        if (head==nullptr){
            std::cout <<"NULL"<< std::endl;
            return;
        }
        print(head->next);
        std::cout << head->data << " -> "; //! PLACEMENT OF PRINT IS IMPORTANT        
    }
};




int main(){

    LL ll;

    // Node n(5);
    Node a(3);
    ll.insert_end(&a);
    Node b(1);
    ll.insert_end(&b);
    Node c(2);
    ll.insert_end(&c);
    Node d(5);
    ll.insert_end(&d);
    Node e(6);
    ll.insert_end(&e);

    ll.print(ll.head);
    
    


    return 0;
}