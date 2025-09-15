/*

Task#4
Solve the following problem using a Singly Linked List.
Given a Linked List of integers, write a function to modify the linked list such that all even numbers appear
before all the odd numbers in the modified linked list. Also, keep the order of even and odd numbers same.
Examples:
Input: 17 -> 15 -> 8 -> 12 -> 10 -> 5 -> 4 -> 1 -> 7 -> 6 -> NULL
Output: 8 -> 12 -> 10 -> 4 -> 6 -> 17 -> 15 -> 5 -> 1 -> 7 -> NULL
Input: 8 -> 12 -> 10 -> 5 -> 4 -> 1 -> 6 -> NULL
Output: 8 -> 12 -> 10 -> 4 -> 6 -> 5 -> 1 -> NULL
// If all numbers are even then do not change the list
Input: 8 -> 12 -> 10 -> NULL
Output: 8 -> 12 -> 10 -> NULL
// If all numbers are odd then do not change the list
Input: 1 -> 3 -> 5 -> 7 -> NULL
Output: 1 -> 3 -> 5 -> 7 -> NULL

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;



class singlyNode
{
public:
    int data;
    singlyNode *next;

    // constructor
    singlyNode(int data){
        this->data = data;
        next = nullptr;
    }
    singlyNode(){
        this->data = 0;
        next = nullptr;
    }
};
class singly_LL
{
public:
    singlyNode* head;
    int length;
    singly_LL(){
        head = nullptr;
    }

    void checkLength(){ // of LL
        singlyNode *temp=head;
        int i =0;
        while(temp!=nullptr){
            temp = temp->next;
            i++;
        }
        this->length = i;
    }

    void insert_end(int data){
        singlyNode *new_node = new singlyNode(data);
        

        if (head == nullptr) 
        {
            head = new_node; 
            return;
        }

        singlyNode *temp = head; 
        while (temp->next!=nullptr)
        {
            
            temp = temp->next;
        }
        
        temp->next = new_node;
    }

    // insert the node in the end of the LL
    void insert_node(singlyNode* node){
        // traverse to the end of node
        
        singlyNode *temp = head; 
        while (temp->next!=nullptr)
        {
            temp = temp->next;
        }
        temp->next = node;
    }

    
    // return the address of the node rather than deleting it
    singlyNode* extract_pos(int pos){
        if (head!=nullptr)
        {
            std::cout << "pos: " <<pos<< std::endl;
            singlyNode *prev = nullptr, *curr = nullptr, *next = head;
            std::cout << "pos: " <<pos<< std::endl;

            

            while (pos-- != 0)
            {
                std::cout << "pos: " <<pos<< std::endl;
                prev = curr;
                curr = next;
                next = next->next;
            }
            // get the prev node to point to next node, leaving the middle node dangling
            if (prev!=nullptr)
            {
                
                prev->next = next;
                // return the dangling node
                
                std::cout << "curr: " <<curr->data<< std::endl;
                return curr;
            } else {
                return curr;
            }
            return nullptr;
        }
        return nullptr;
    }

    void print(){
        singlyNode *temp = head; // a temporary pointer to traverse through the LL
        while (temp!=nullptr)
        {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout <<"NULL"<< std::endl;
        
    }
};



int main(){

    singly_LL ll;
    ll.insert_end(17);
    ll.insert_end(15);
    ll.insert_end(8);
    ll.insert_end(12);
    ll.insert_end(10);
    ll.insert_end(5);
    ll.insert_end(4);
    ll.insert_end(1);
    ll.insert_end(7);
    ll.insert_end(6);

    ll.print();

    //place all the odds to the end, for this create a new LL, and insert all the odd nodes to that
    //then place the extracted node into the oddLL

    singly_LL oddLL;
    
    singlyNode *temp = ll.head, *extractedNode=nullptr;
    int i = 1; // the LL as 1-indexing
    while (temp->next != nullptr)
    {
        cout << i<< endl;
        // if odd
        if (temp->data % 2 != 0)
        {
            std::cout << "/* message */" << std::endl;
            extractedNode = ll.extract_pos(i);
            std::cout << "extractedNode->data " << extractedNode->data << std::endl;
            oddLL.insert_node(extractedNode);
        }
        i++;
        
    }
    ll.print();
    oddLL.print();
    

    return 0;
}