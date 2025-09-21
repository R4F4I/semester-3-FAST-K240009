/*



* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;


class Node
{
public:
    int data;
    Node *next;

    // constructor
    Node(int data){
        this->data = data;
        next = nullptr;
    }
    Node(){
        this->data = 0;
        next = nullptr;
    }
};
class singly_LL
{
public:
    Node* head;
    int length;
    singly_LL(){
        head = nullptr;
    }


    void insert_end(int data){
        Node *new_node = new Node(data);
        if (head == nullptr) 
        {
            head = new_node; 
            return;
        }
        Node *temp = head; 
        while (temp->next!=nullptr)
        {   
            temp = temp->next;
        }
        temp->next = new_node;
    }



    void print(){
        Node *temp = head; 
        while (temp!=nullptr)
        {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("\n");
        
    }
};

Node* middleOfLL(singly_LL ll, Node* slow, Node* fast){

    // if fast has reached the end node return slow, as it has most likely reached the middle
    if (fast->next==nullptr || fast->next->next == nullptr)
    {
        return slow;
    }
    
    // since fast is traversing twice  many steps as slow
    return middleOfLL(ll, slow->next,fast->next->next);

}


int main(){

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
    ll.insert_end(11);
    ll.insert_end(12);


    Node* middle = middleOfLL(ll,ll.head,ll.head);

    std::cout << middle->data << std::endl;




    return 0;
}