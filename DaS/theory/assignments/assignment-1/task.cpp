/*

A
company maintains a custom messaging
system where each message is stored as a node in a singly linked list. Each node points
to the next message in sequence. Occasionally, due to a software bug or data corruption, a message points back to an
earlier message in the list, forming a cycle.
This leads to infinite processing loops,
causing message delivery to fail or the system to crash.


Design and implement a for the in-memory
linked list used in the messaging queue.


The system should:


1.     Detect
if a cycle exists in the linked list of messages.


2.     Identify
the starting node of the cycle.


3.     Break
the cycle by setting the last node's next pointer to null.


4.     Return
the corrected, acyclic message queue.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;


/* 

idea:

all nodes point to a unique pointer

if two nodes point to the same node, then a loop is present in LL

to break it, make the 2nd node point to nullptr

*/


// create LL class


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

    void print(){
        singlyNode *temp = head; // a temporary pointer to traverse through the LL
        while (temp!=nullptr)
        {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("\n");
        
    }
};


template <typename T>
class dynamicList{
    T **list ;
    int length; // size of array
    
    
    void allocateSpace(){
        T **newArr = new T*[length+5];
        for (size_t i = 0; i < length; i++)
        {
            newArr[i] = list[i];
        }
        length+=5;
        delete[] list;
        list = newArr;

        // assign null values to the new arr
        for (size_t i = length; i < length+5; i++)
        {
            list[i] = nullptr;
        }
        
    }

    void checkPop(){
        population = 0;
        for (size_t i = 0; i < length; i++)
        {
            if (list[i]!=0)
                population++;
        }
        
    }

public:
    int population; // num of members / non empty blocks
    dynamicList(){
        list = new T*[5];

        for (size_t i = 0; i < 5; i++){
            list[i] = nullptr;
        }
        length = 5;
        population = 0;
        
    }

    dynamicList(T* val){
        dynamicList();
        list[0] = val;
    }

    void addVal(T* score){
        checkPop();
        if (length - population<3){
            // allocate memory to the marks array
            allocateSpace();
        }
        
        list[population] = score;
        population++;

    }

    // compares the last val of list with all prev values, works for only one other duplicate, if found returns true
    bool checkDuplicate(){
        for (int i = 0; i < population; i++)
        {
            if (list[i]==list[population])
            {
                return true;
            }
            
        }
        return false;
        
    }


    void print(){
        checkPop();
        for (size_t i = 0; i < population; i++)
        {
            std::cout << list[i] << " ";
        }
        std::cout << std::endl;
    }

};



int main(){

    // create a lengthy linked list
    singly_LL ll;
    ll.insert_end(1);
    ll.insert_end(2);
    ll.insert_end(3);
    ll.insert_end(4);
    ll.insert_end(5);
    ll.insert_end(6);
    ll.insert_end(7);
    ll.insert_end(8);
    ll.insert_end(9);
    ll.insert_end(10);

    ll.print();

    // Create a cycle for testing: make the last node point to the 3rd node (data = 3)
    singlyNode* temp = ll.head;
    std::cout << "temp: "<< temp << std::endl;
    singlyNode* cycleStart = nullptr;
    std::cout << "cycleStart: "<< cycleStart << std::endl;
    while (temp->next != nullptr) {
        std::cout << "cycleStart: "<< cycleStart << std::endl;
        if (temp->data == 3) {
            cycleStart = temp;
        }
        temp = temp->next;
    }
    if (cycleStart != nullptr) {
        temp->next = cycleStart;
    }

    // Cycle detection and breaking logic
    dynamicList<singlyNode> pointers;

    
    singlyNode *temp2 = ll.head;
    
    while (temp2->next !=nullptr)
    {
        pointers.addVal(temp2);
        pointers.print();
        temp2 = temp2->next;
        if (pointers.checkDuplicate())
        {
            pointers.print();
            // if the latest entry in the list is a duplicate then that means that temp2->next must be made into a nullptr
            temp2->next = nullptr;
        }
        
    }
    


    std::cout << "--------------------------" << std::endl;
    
    ll.print();
    std::cout << "--------------------------" << std::endl;
    




    return 0;
}