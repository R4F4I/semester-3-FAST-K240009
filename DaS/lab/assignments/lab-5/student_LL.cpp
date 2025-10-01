/* 
display 5 student object in linkedlist

 */

#include <iostream>

using namespace std;

class Student{
private:

    int id;
    string name;

public:
    Student(){
        id=0;
        name = "null";
    }
    Student(int id, string name) {
        this->id=id;
        this->name=name;
    }

    void setID(int id){
        this->id = id;
    }
    void setname(string name){
        this->name = name;
    }

    void display(){
        cout<<"id: "<<this->id<<" name: "<<this->name;
    }
    
};


///////////////////////////////////////////////////////

struct Node
{
    Student data;
    Node *next, *prev;
};



class LL
{
public:
    Node* head;
    LL(){
        head = nullptr;
    }

    void insert_end(Student& data){
        Node *new_node = new Node;

        new_node->data = 

        if (head == nullptr) 
        {
            head = node; 
            return;
        }
        Node *temp = head; 
        while (temp->next!=nullptr)
        {
            temp = temp->next;
        }
        temp->next = node;
    }
    void print(Node* head){
        if (head==nullptr){
            std::cout <<"NULL"<< std::endl;
            return;
        }
        print(head->next);
        head->data.display();
        std::cout << " -> "; //! PLACEMENT OF PRINT IS IMPORTANT        
    }
};




int main(){

    LL ll;

    Node a = new Node();
    a.data.setID(1);
    a.data.setname("a");
    ll.insert_end(&a);
    
    Node b = new Node();
    b.data.setID(2);
    b.data.setname("b");
    ll.insert_end(&b);
    
    Node c = new Node();
    c.data.setID(3);
    c.data.setname("c");
    
    ll.insert_end(&c);
    
    Node d = new Node();
    d.data.setID(4);
    d.data.setname("d");
    
    ll.insert_end(&d);
    
    Node e = new Node();
    e.data.setID(5);
    e.data.setname("e");

    ll.insert_end(&e);

    ll.print(ll.head);
    
    


    return 0;
}