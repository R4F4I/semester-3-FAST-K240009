/* 
how the linked list will work
a head pointer will be null initially
at insert a new node will be created and the head pointer will point to it
the new node will have its next pointer pointing to null
*/

#include <stdio.h>

class node
{
public:
    int data;
    node *next;

    // constructor
    node (int data){
        this->data = data;
        next = NULL;
    }
};

class singly_LL
{
private:
    node* head;
public:
    singly_LL(){
        head = NULL;
    }

    // insert a data at the end of the node
    void insert_end(int data){ // pass the head pptr's address to pass byref
        // allocate memory (using new) of size node, return type pointer of node, why? to prevent the local var from being destroyed when the function ends (DMA prevents the var from being destroyed automatically) 
        node *new_node = new node(data);
        
        // check if value of head ptr is NULL
        if (head == NULL) // the value of head ptr
        {
            head = new_node;
            return;
        }

        // move to the end of the linked list and get the last node to point to the new node
        
        node *temp = head; // copy head pointer's value into temp
        while (temp->next!=NULL)
        {
            // temp->next is sam (*temp).next, meaning temp is being dereferenced and the next value of that node is being store in the temp pointer
            temp = temp->next;
        }
        // now that temp is null, get it to store the new_node's address
        temp->next = new_node;
    }

    void print(){
        node *temp = head; // a temporary pointer to traverse through the LL
        while (temp!=NULL)
        {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("\n");
        
    }
};


int main (){

    singly_LL ll;

    ll.insert_end(11);
    ll.insert_end(10);
    ll.insert_end(20);
    ll.insert_end(30);
    ll.insert_end(40);
    ll.insert_end(50);

    ll.print();

    return 0;
}