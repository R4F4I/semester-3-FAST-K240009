/* 
how the linked list will work
a head pointer will be null initially
at insert a new node will be created and the head pointer will point to it
the new node will have its next pointer pointing to null
*/

#include <stdio.h>

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

    void insert_start(int data){
        
        singlyNode *new_node = new singlyNode(data);
        
        // empty LL checker
        if (head == NULL) // the value of head ptr
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

        singlyNode *prev=NULL, *next=head;


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
    

    void reverse_LL(){
        if (head == NULL)
        {
            return;
        }
        // need 3 pointers
        singlyNode *prev=NULL, *curr=NULL, *next=this->head;

        while (next!=NULL)
        {
            // progress forward or 'crawl' through the LL
            prev = curr;
            curr = next;
            next = next->next;

            // reverse the pointer of the curr node
            curr->next = prev;
        }
        // then the head will point to the last node, since next will be NULL meaning curr will point to the last node
        head = curr;
        
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


class doublyNode
{
public:
    int data;
    doublyNode *prev, *next;

    // constructor
    doublyNode(int data){
        this->data = data;
        prev = NULL;
        next = NULL;
    }
};


class doubly_LL
{
public:
    doublyNode *head;

    doubly_LL(){
        head = NULL;
    }

    void insert_end(int data){
        doublyNode *new_node = new doublyNode(data);
        if (head==NULL)
        {
            head = new_node;
            new_node->prev = NULL; // first node has no prev node to point to
            return;
        }

        doublyNode *temp = head;
        while (temp->next!=NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp; // new node will also point to prev node
        


        
    }

    void reverse_LL(){
        // simply switch the prev pointer, and next pointer values

        if (head!=NULL)
        {
            doublyNode *prev = NULL, *temp = head, *swap = NULL; // to be used to swap the place of both pointers
            // 2 pointers will be used, swap will occur using prev pointer, temp will be used to traverse ahead
            while (temp->next!=NULL)
            {
                prev = temp;
                temp = temp->next;

                swap = prev->prev;
                prev->prev = prev->next;
                prev->next = swap;
            }
        }
    }
    void print(){
        doublyNode *temp = head; // a temporary pointer to traverse through the LL
        while (temp!=NULL)
        {
            printf("%p | ", temp->prev);
            printf("%d | ", temp->data);
            printf("%p", temp->next);
            printf("\n");
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
    ll.reverse_LL();
    ll.print();
    
    ll.insert_start(12);
    ll.print();
    ll.insert_pos(3,55);
    ll.print();

    ll.remove_start_v2();
    ll.print();

    ll.remove_end();
    ll.print();
    ll.remove_pos(3);
    ll.print();
    
    doubly_LL newLL;
    
    printf("################\n");
    
    newLL.insert_end(11);
    newLL.print();
    newLL.insert_end(10);
    newLL.insert_end(20);
    newLL.insert_end(30);
    newLL.insert_end(40);
    newLL.insert_end(50);

    newLL.print();


    // newLL.reverse_LL();
    // newLL.print();

    return 0;
}