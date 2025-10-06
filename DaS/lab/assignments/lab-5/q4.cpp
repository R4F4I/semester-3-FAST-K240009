/*

Task #4 Create a C++ program to search for a value in a singly linked list, using non-tail recursion?

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
    singlyNode *head, *tail;
    
    singly_LL(){
        head = nullptr;
    }



    // insert a data at the end of the node
    void insert_end(int data){
        singlyNode *new_node = new singlyNode(data);
        if (head == nullptr)
        {
            head = new_node;
            tail = new_node;
            return;
        }
        
        singlyNode *temp = new_node;
        tail->next = new_node; // get last node (who tail is pointing at) to point at new_node
        tail = new_node;    // get tail to point to new_node
    
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

// check if the value exists
bool find_val(int val, singlyNode* head){

    if (head==nullptr) // reached end of node
    {
        return false;
    }
    if (head->data==val)
    {
        return true;
    }
    return find_val(val, head->next);

}


int main(){

    singly_LL ll;

    ll.insert_end(3);
    ll.insert_end(1);
    ll.insert_end(2);
    ll.insert_end(5);
    ll.insert_end(6);

    ll.print();

    std::cout << find_val(2,ll.head) << std::endl;
    std::cout << find_val(17,ll.head) << std::endl;
    

    return 0;
}