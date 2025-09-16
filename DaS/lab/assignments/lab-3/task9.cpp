/*

Task#9:
Given a linked list, you have to perform the following task:
1. Extract the alternative nodes starting from second node.
2. Reverse the extracted list.
3. Append the extracted list at the end of the original list.
Note: Try to solve the problem without using any extra memory.
Example 1:
Input:
LinkedList = 10->4->9->1->3->5->9->4
Output:
10 9 3 9 4 5 1 4
Explanation:
Alternative nodes in the given linked list are 4,1,5,4. Reversing the alternative nodes from the given list, and then
appending them to the end of the list results in a list 10->9->3->9->4->5->1->4.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

// extract the nodes in alternating fashion, place these extracted nodes into a new LL, reverse that LL, then merge it
// for effiecney this ll has tail pointer


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
    singlyNode *head, *tail;
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

    void merge(singlyNode ll){

    }

    void insert_end(int data){
        singlyNode *new_node = new singlyNode(data);
        

        if (head == nullptr) 
        {
            head = new_node; 
            tail = new_node;
            return;
        }

        tail->next = new_node; // get last node to point to new node
        tail = new_node; // tail now points to new last node
    }

    // insert the node in the end of the LL
    void insert_node(singlyNode* node){

        // cout<<"insert"<<endl;
        if (head == nullptr)
        {
            head = node;
            tail = node;
            return;
        }
        

        tail->next = node;
        tail = node;
    }

    
    // return the address of the node rather than deleting it, assume, if pos is last, get tail to retract, for this remove 
    singlyNode* extract_pos(int pos){
        checkLength();
        // if it is the last node to be extracted
        if (pos == this->length)
        {
            // the position is the last node, for this simply get the 2nd last node to point to null 
            singlyNode *curr = nullptr, *next = head;
            while (next->next != nullptr)
            {
                curr = next;
                next = next->next;
            }
            tail = curr;
            tail->next = nullptr;

            return next;
        }
        
        if (head!=nullptr)
        {
            singlyNode *prev = nullptr, *curr = nullptr, *next = head;

            while (pos-- != 0)
            {
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

    ll.insert_end(10);
    ll.insert_end(4);
    ll.insert_end(9);
    ll.insert_end(1);
    ll.insert_end(3);
    ll.insert_end(5);
    ll.insert_end(9);
    ll.insert_end(4);

    ll.print();

    // extract alternative nodes and place them into a new ll

    singly_LL newLL;
    singlyNode *tempNode;

    for (size_t i = 1; i < 9; i++)
    {
        if (i%2==0)
        {
            tempNode = ll.extract_pos(i);
            newLL.insert_node(tempNode);
        }
        
    }
    newLL.print();




    return 0;
}