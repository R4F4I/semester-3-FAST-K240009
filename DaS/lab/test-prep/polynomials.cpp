/*

https://github.com/MuxammilSidd/FAST-KHI-Semester-3/blob/main/Data%20Structures%20(LAB)/Past%20Papers/Mid-Terms/DSA%20Lab%20Mid%20A%20(Unspecified%20Paper).pdf

LL1: 4x7 + 2x6 - x3 + 4x2 + 3 = 0
LL2: 2x8 + 3x3 - 2 = 0

res: 2x8 + 4x7 + 2x6 + 2x3 + 4x2 + 1 = 0

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;


class Node{

public:
    int data;
    Node* next;

    Node(int d){
        data = d;
        next = nullptr;
    }

};

class ll{

public:
    Node *head, *tail;

    ll(){
        head = nullptr;
        tail = nullptr;
    }

    ll operator+ (ll& other){
        Node* temp = head;
        Node* temp2 = other.head;
        ll res;
        while (temp!=nullptr && temp2 !=nullptr)
        {

            if (temp==nullptr)
            {
                std::cout << "null" << std::endl;
                res.insertVal(0 + temp2->data);

            } 
            
            else if (temp2==nullptr)
            {
                std::cout << "null2" << std::endl;
                res.insertVal(temp->data + 0);
            } 
            
            else
            {
                res.insertVal(temp->data + temp2->data);
                temp = temp->next;
                temp2 = temp2->next;
            }
            
        }
        std::cout << temp2 << std::endl;
        return res;
    }

    void insertVal(int data){
        Node* node = new Node(data);

        if (head==nullptr)
        {
            head = node;
            tail = node;
            return;
        }
        
        tail->next = node;
        tail = node;

    }

    // has to be printed in polynomial style, zeros will be ignored
    void printL(){
        Node* temp = head;
        int i = 0;
        while (temp!=nullptr)
        {
            if (temp->data!=0)
            {
                std::cout << temp->data << "x"<<i<<" + ";
            }
            i++;
            temp=temp->next;
        }
        std::cout << "=0" << std::endl;
    }

    void differentiate(){
        Node* temp = head;

        int i = 0;
        // represents Anx**n
        while (temp!=nullptr)
        {
            temp->data = i*(temp->data);
            temp = temp->next;
            i++;
        }
        // after this remove the first node to represent n-1 for Ax**n
        temp = head;
        head = head->next;
        delete temp;    
    }

};


int main(){


    /* 
    LL1: 4x7 + 2x6 - x3 + 4x2 + 3 = 0
    LL2: 2x8 + 3x3 - 2 = 0

    res: 2x8 + 4x7 + 2x6 + 2x3 + 4x2 + 1 = 0
     */

     
     ll LL1;
     LL1.insertVal(3);
     LL1.insertVal(0);
     LL1.insertVal(4);
     LL1.insertVal(-1);
     LL1.insertVal(0);
     LL1.insertVal(0);
     LL1.insertVal(2);
     LL1.insertVal(4);
     LL1.insertVal(0);
     
     LL1.printL();
     
     ll LL2;
     
     LL2.insertVal(-2);
    LL2.insertVal(0);
    LL2.insertVal(0);
    LL2.insertVal(3);
    LL2.insertVal(0);
    LL2.insertVal(0);
    LL2.insertVal(0);
    LL2.insertVal(0);
    LL2.insertVal(2);
    
    
    LL2.printL();
    
    ll res = LL1 + LL2;

    res.printL();

    LL1.differentiate();
    LL1.printL();

    return 0;
}