/*

Task#8:
Give an efficient algorithm for concatenating two doubly linked lists L and M, with head and tail preserved
nodes, into a single list that contains all the nodes of L followed by all the nodes of M.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>
#include <iomanip>

using namespace std;



class doublyNode
{
public:
    int data;
    doublyNode *prev, *next;

    // constructor
    doublyNode(int data){
        this->data = data;
        prev = nullptr;
        next = nullptr;
    }
};


class doubly_LL
{
public:
    doublyNode *head, *tail;

    doubly_LL(){
        head = nullptr;
        tail = nullptr;
    }

    void insert_end(int data){
        doublyNode *new_node = new doublyNode(data);
        if (head==nullptr)
        {
            head = new_node;
            new_node->prev = nullptr; // first node has no prev node to point to
            tail = new_node;
            return;
        }

        // tail points to last node

        tail->next = new_node; // last node point to new node
        new_node->prev = tail; // new node points to prev node
        tail = new_node; // tail points to new node

    }

    void insert_start(int data){
        doublyNode *node = new doublyNode(data);

        // new node will point to where head is pointing
        node->next = head;
        // head will point to new node
        head = node;
    }

    void reverse_LL(){
        // simply switch the prev pointer, and next pointer values
        // point head to the last node
        // a single temp pointer will traverse through the LL, and swap the pointers, the last node will be head

        doublyNode *temp = head, *swap;
        while (temp->next!=nullptr)
        {
        
            // swap
            swap = temp->next;
            temp->next = temp->prev;
            temp->prev = swap;
            
            temp = temp->prev;
        }
        
        // after reaching last node, perform last swap
        swap = temp->next;
        temp->next = temp->prev;
        temp->prev = swap;

        doublyNode *newTemp;

        // head and tail will switch places
        newTemp = head;
        head = tail;
        tail = newTemp;
        
    }
    void printNode(doublyNode* node){
        std::cout << "node: ";
        std::cout << std::setw(13) << node->prev << " | " << node->data << " | " << node->next << std::setw(13) << "    <--- " << node << std::endl;
    }

    // merge this ll into the object
    void merge(doubly_LL ll){

        // for this get the one calling is L, and the arg is M
        // get tail of L to point to the M head node, and the head node to point to L's tail
        tail->next = ll.head;
        ll.head->prev = tail;
        // the M tail will be new tail
        tail = ll.tail;
    }

    void print(){
        doublyNode *temp = head; // a temporary pointer to traverse through the LL

        while (temp!=nullptr)
        {
            if (temp == head)
            {
                // std::cout << "head->" << head << std::endl;
                std::cout << std::setw(12) <<"head-> "  <<  temp->prev << " | " << temp->data << " | " << temp->next << std::setw(15) << "    <--- " << temp << std::endl;
            }else
            {
                std::cout << std::setw(13) << temp->prev << " | " << temp->data << " | " << temp->next << std::setw(13) << "    <--- " << temp << std::endl;
            }
            
            

            temp = temp->next;
        }
        
    }
};




int main(){

    doubly_LL L;
    L.insert_end(2);
    L.insert_end(3);
    L.insert_end(4);
    L.insert_end(5);

    L.print();

    std::cout << "---------" << std::endl;
    
    doubly_LL M;
    M.insert_end(6);
    M.insert_end(7);
    M.insert_end(8);
    M.insert_end(9);
    
    M.print();
    std::cout << "---------" << std::endl;

    L.merge(M);

    L.print();


    return 0;
}