/*

Task#6
Delete a value from any position (not the first one only) from the singly linked list if it’s present in the
list otherwise show a message to the user that the value is not present in the list.

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
        next = NULL;
    }
    singlyNode(){
        this->data = 0;
        next = NULL;
    }
};
class singly_LL
{
public:
    singlyNode* head;
    int length;
    singly_LL(){
        head = NULL;
    }

    void checkLength(){ // of LL
        singlyNode *temp=head;
        int i =0;
        while(temp!=NULL){
            temp = temp->next;
            i++;
        }
        this->length = i;
    }



    // insert a data at the end of the node
    void insert_end(int data){
        // allocate memory (using new) of size node, return type pointer of node, why? to prevent the local var from being destroyed when the function ends (DMA prevents the var from being destroyed automatically) 
        // also new_node is pointer to this DMA created node, it contains the node's address not its value
        singlyNode *new_node = new singlyNode(data);
        
        // empty LL checker
        if (head == NULL) // the value of head ptr
        {
            head = new_node; // copy the new_nodes address into head
            return;
        }

        // traverse to the end of ll
        
        singlyNode *temp = head; // copy head pointer's value into temp
        while (temp->next!=NULL)
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
        if (head!=NULL)
        {
            singlyNode *prev=NULL, *next=head;
            // traverse to end with 2 pointers
            while (next->next!=NULL) // check whether the next pointer is pointing to the last node
            {
                prev = next;
                next = next->next;
            }
            prev->next = NULL;
            // this will leave a dangling node

            delete next; // deleting the dangling node
        }
    }

    // remove node at nth position
    void remove_pos(int pos){
        if (pos==1)
        {
            remove_start_v2();
            return;
        } else
        {
            if (head!=NULL)
            {
                checkLength();
                if (pos>this->length)
                {
                    return;
                }
                singlyNode *prev = NULL, *curr = NULL, *next = head;
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
    }

    void print(){
        singlyNode *temp = head; // a temporary pointer to traverse through the LL
        while (temp!=NULL)
        {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("\n");
        
    }
};



int main(){

    singly_LL ll;

    ll.insert_end(2);
    ll.insert_end(3);
    ll.insert_end(4);
    ll.insert_end(5);
    ll.insert_end(6);
    ll.insert_end(7);
    ll.insert_end(8);
    ll.insert_end(9);
    
    ll.print();

    // removing from 3
    ll.remove_pos(3);
    ll.print();
    // removing from 3
    ll.remove_pos(3);
    ll.print();



    return 0;
}