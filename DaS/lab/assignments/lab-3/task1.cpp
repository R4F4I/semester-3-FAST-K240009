/*

Task#1:
You are given the array (3 1 2, 5, 8) of size 5 print that array on screen. Then create singly linked list from
that array , Now add the 9 at the end , 11 pos 3, and 4 at the front and list. Now delete the 1, 2, and 5 then
print the linked list.

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

    void insert_start(int data){
        
        singlyNode *new_node = new singlyNode(data);
        
        // empty LL checker
        if (head == nullptr) // the value of head ptr
        {
            head = new_node;
            return;
        } else {
            new_node->next = head; // copy the value of head / new_node is pointing where is head is pointing
            head = new_node; // head now points to the new node
            return;
        }
    }

    void insert_pos(int pos, int data){
        
        // before traversal check length of ll to prevent invalid positions
        checkLength();
        
        if (pos>this->length)
        {
            return;
        } 

        singlyNode *new_node = new singlyNode(data);

        int i = 0;

        singlyNode *prev=nullptr, *next=head;


        while (i!=pos)
        {
            prev = next;
            next = next->next;
            i++;
        }
        // now that temp has traversed to the position, add new_node here
        prev->next = new_node; // change the address value of the node temp is pointing at, to point to new_node
        new_node->next = next; // change the new_node to point to the next node
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


    void remove_start(){
        // the head will simply point to the next node
        head = head->next;
        // this will leave a dangling node
    }

    // delete the first node (conserve memory)
    void remove_start_v2(){
        
        singlyNode *temp = head; // temp will point to first node
        
        remove_start();
        
        delete temp; // deleting the dangling node
    }


    // 2nd last node will simply point to null
    void remove_end(){
        if (head!=nullptr)
        {
            singlyNode *prev=nullptr, *next=head;
            // traverse to end with 2 pointers
            while (next->next!=nullptr) // check whether the next pointer is pointing to the last node
            {
                prev = next;
                next = next->next;
            }
            prev->next = nullptr;
            // this will leave a dangling node

            delete next; // deleting the dangling node
        }
    }

    // remove node at nth position
    void remove_pos(int pos){
        if (head!=nullptr)
        {
            checkLength();
            if (pos>this->length)
            {
                return;
            }
            singlyNode *prev = nullptr, *curr = nullptr, *next = head;
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

    void remove_val(int data){
        singlyNode *curr = nullptr, *prev=nullptr, *next = head;
        // traverse through the entire LL
        while (next != nullptr)
        {
            prev = curr;
            curr = next;
            next = next->next;

            if (curr->data == data)
            {
                // prev node will point to next
                prev->next = next;
                // delete the curr node
                delete curr;
            }
        }
    }
    

    void reverse_LL(){
        if (head == nullptr)
        {
            return;
        }
        // need 3 pointers
        singlyNode *prev=nullptr, *curr=nullptr, *next=this->head;

        while (next!=nullptr)
        {
            // progress forward or 'crawl' through the LL
            prev = curr;
            curr = next;
            next = next->next;

            // reverse the pointer of the curr node
            curr->next = prev;
        }
        // then the head will point to the last node, since next will be nullptr meaning curr will point to the last node
        head = curr;
        
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

    ll.insert_end(3);
    ll.insert_end(1);
    ll.insert_end(2);
    ll.insert_end(5);
    ll.insert_end(6);

    ll.print();
    
    ll.insert_end(9);
    ll.insert_pos(3,11);
    
    ll.insert_start(4);
    
    ll.print();
    ll.remove_val(1);
    ll.remove_val(2);
    ll.remove_val(5);

    


    return 0;
}