/*

Task 2: Suppose you are implementing a program to keep track of a user's web browsing history using
a linked list and a stack. Whenever the user visits a new website, the website URL is added to the front
of the linked list to represent the most recent page visited. Additionally, the website URL is pushed
onto a stack to allow for the user to easily navigate back to the previous page.
Now suppose the user has visited 5 websites in the following order: Google, Facebook, Twitter,
LinkedIn, and Instagram. The user decides to click the "back" button twice to return to the Facebook
page. Write a function to implement this behavior using the linked list and stack.
Hint: You will need to pop two elements from the stack and remove the first two nodes from the
linked list.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

template <typename T>
class Node{

public:
    T data;
    Node* next = nullptr;

    Node(T data){
        this->data = data;
        next = nullptr;
    }

 };

template <typename T>
class Stack{

public:
    Node<T> *head, *tail;
    Stack(){
        head =nullptr;
        tail =nullptr;
    }

    void push(T data){
        Node<T>* newNode = new Node(data);
        if (head==nullptr)
        {
            head = newNode;
            tail = newNode;
            return;
        }
        
        tail->next = newNode;
        tail = newNode;


    }

    T pop(){
        T val = tail->data;

        Node<T>* temp = head;
        // traverse till prev node
        while (temp->next != tail)
        {
            temp = temp->next;
        }
        tail = temp; // new tail is prev node
        temp = temp->next; // traverse one more time to remove the last node 
        delete temp; // last node removed
        
        return val;
    }

    void print(){
        Node<T>* temp = head;
        while (temp!=tail->next)
        {
            std::cout << temp->data <<std::endl;
            temp = temp->next;
        }
        cout << endl << endl;

    }

};



int main(){

    Stack<string> appStack;

    
    appStack.push("Google");
    appStack.push("Facebook");
    appStack.push("Twitter");
    appStack.push("LinkedIn");
    appStack.push("Instagram");

    appStack.print();
    
    // pop 2 sites
    appStack.pop();
    appStack.pop();
    
    appStack.print();


    return 0;
}