/*

Task#5
Solve the following problem using a Singly Linked List.
Given a Linked List of integers or string, write a function to check if the entirety of the linked list is a
palindrome or not
Examples:
Input: 1 -> 0 -> 2 -> 0 -> 1 -> NULL
Output: Linked List is a Palindrome
Input: B -> O -> R -> R -> O -> W -> O -> R -> R -> O -> B -> NULL
Output: Linked List is a Palindrome

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

// for palindrome checking, reach the middle of LL, then 'break' the LL, then reverse the end half of the LL, then compare from the two ends, 


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
    void print(){
        std::cout << this->data << " "<< this->next << std::endl;
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
    // insert a data at the end of the node
    void insert_end(int data){
        // allocate memory (using new) of size node, return type pointer of node, why? to prevent the local var from being destroyed when the function ends (DMA prevents the var from being destroyed automatically) 
        // also new_node is pointer to this DMA created node, it contains the node's address not its value
        singlyNode *new_node = new singlyNode(data);
        
        // empty LL checker
        if (head == nullptr) // the value of head ptr
        {
            head = new_node; // copy the new_nodes address into head
            return;
        }

        // traverse to the end of ll
        
        singlyNode *temp = head; // copy head pointer's value into temp
        while (temp->next!=nullptr)
        {
            // temp->next is sam (*temp).next, meaning temp is being dereferenced and the next value of that node is being store in the temp pointer
            temp = temp->next;
        }
        // now that temp is null, get it to store the new_node's address
        temp->next = new_node;
    }
    
    // insert the node in the end of the LL
    void insert_node(singlyNode* node){
        // traverse to the end of node
        if (head == nullptr)
        {
            // std::cout << "1st node" << std::endl;
            head = node;
        } else{
            singlyNode *temp = head; 
            while (temp->next!=nullptr)
            {
                temp = temp->next;
            }
            temp->next = node;
        }
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
    
    bool isPalindrome(){
        // create a copy of the original LL
        singly_LL ll;
        singlyNode* temp=head; // point to the original LL head
        singlyNode* node = new singlyNode(*temp);
        while (temp!=nullptr)
        {
            node = temp; // copy the node BY VAL, temp is pointing into 'node'
            temp = temp->next; // traverse
            // make node point to null
            node->next = nullptr;
            ll.insert_node(node);
        }
        
        // reach to the middle of LL using slowP, fastP approach

        singlyNode *slowP =ll.head; 
        singlyNode *fastP = ll.head;

        while (fastP != nullptr && fastP->next !=nullptr)
        {
            slowP = slowP->next;
            fastP = fastP->next->next;
        }
        // reverse LL from middle to end
        fastP = ll.reverse_LL(slowP);
        // now since the fastP is at end, compare the nodes from head and fastP
        temp = head;
        while (temp!=fastP && temp!=nullptr && fastP != nullptr)
        {
            temp = temp->next;
            fastP = fastP->next;

            if (temp->data != fastP->data)
            {
                return false;
            }
        }
        return true;
    }

    // will not make the last node point to null
    singlyNode* reverse_LL(singlyNode* start){
        if (head == nullptr)
        {
            return nullptr;
        }
        // need 3 pointers
        singlyNode *prev=nullptr, *curr=nullptr, *next=start; // reverse LL from the starting point

        while (next!=nullptr)
        {
            // progress forward or 'crawl' through the LL
            prev = curr;
            curr = next;
            next = next->next;

            // reverse the pointer of the curr node
            curr->next = prev;
        }
        // return the pointer to the new beginning
        return curr;
        
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
    ll.insert_end(1);
    ll.insert_end(0);
    ll.insert_end(2);
    ll.insert_end(0);
    ll.insert_end(1);
    ll.print();

    std::cout << "is palindrome:" << ll.isPalindrome()<<std::endl;

    return 0;
}