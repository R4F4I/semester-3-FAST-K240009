/*

Task 1: Suppose you are building a program to manage a to-do list for a busy professional. You decide
to use a stack to keep track of the items on the list. Write a code snippet that demonstrates how you
would add a new item to the top of the stack, check if the stack is empty, and remove the top item
from the stack.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

class Node{

public:
    int data = 0;
    Node* next = nullptr;

    Node(int data){
        this->data = data;
        next = nullptr;
    }

 };

class Stack{

public:
    Node *head, *tail;
    Stack(){
        head =nullptr;
        tail =nullptr;
    }

    void push(int data){
        Node* newNode = new Node(data);
        if (head==nullptr)
        {
            head = newNode;
            tail = newNode;
            return;
        }
        
        tail->next = newNode;
        tail = newNode;


    }

    int pop(){
        int val = tail->data;

        Node* temp = head;
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
        Node* temp = head;
        while (temp!=tail->next)
        {
            std::cout << temp->data <<std::endl;
            temp = temp->next;
        }
        cout << endl << endl;

    }

};


int main(){


    Stack newStack;

    newStack.push(10);
    newStack.push(20);
    newStack.push(30);
    newStack.push(40);
    newStack.push(50);

    newStack.print();
    newStack.pop();
    newStack.print();



    return 0;
}