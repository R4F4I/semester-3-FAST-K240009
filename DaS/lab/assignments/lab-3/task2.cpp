/*

Task#2:
Write a program that prompts the user to enter a number indicating how many elements to move to the
end of a linked list. The program should then move that exact number of elements from the beginning of
the linked list to the end.
Example: given list: 5, 3 1 8 6 4 2
Enter the number: 2
After rotation: 1 8 6 4 2 5 3

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

// for rotation, 
// get the head to point to the 2nd node,
// 1st node will point to null, 
// then get the last node to point to 1st node


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


    // for rotation, 
    // get the head to point to the 2nd node,
    // 1st node will point to null, 
    // then get the last node to point to 1st node

    void rotate(int times = 1){
        for (size_t i = 0; i < times; i++)
        {
            singlyNode *temp = head;
            // first, get last node to point to 1st
            while (temp->next!=nullptr)
            {
                temp = temp->next;
            }
            temp->next = head;
            // std::cout << temp->next->data << std::endl;
            

            
            // get head to traverse ahead
            head = head->next;
            // std::cout << head->data << std::endl;

            // get 1st node to point to null, for this get temp to traverse once more
            temp = temp->next;
            // std::cout << temp->next->data << std::endl;
            temp->next = nullptr;

        }

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

    ll.insert_end(5);
    ll.insert_end(3);
    ll.insert_end(1);
    ll.insert_end(8);
    ll.insert_end(6);
    ll.insert_end(4);
    ll.insert_end(2);
    std::cout << "the current list: ";
    ll.print();
    ll.rotate(2);
    std::cout << "after rotation: ";
    ll.print();
    

    return 0;
}