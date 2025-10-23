/*



* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;


// suppose an arr, with val k, k is a window of size < arr.size

// k will slide through the arr, and create a sum and place it in new,
// this will create a new arr of same size that will have all the slided sums, find the largest val

class Node{

public:
int data;
Node *next, *prev;

Node(int data=0){
        this->data = data;
        next = nullptr;
        prev = nullptr;
        
    }
};

class Q {
    
public:
    Node *head, *tail;

    void Enq(int data){

        Node* newNode = new Node(data);


        if (head == nullptr){
            head = newNode;
            tail = newNode;
            return;
        }

        head->prev = newNode;
        newNode->next = head;
        head = newNode;

    }
    int Deq(){

        if (tail == nullptr)
        {
            return 0;
        }

        int val = tail->data;
        Node* temp = tail;
        tail = tail->prev;
        delete temp;
        return val;
    }

    int sum(){
        int sum = 0;
        Node* temp = head;
        while (temp != tail)
        {
            sum += temp->data;
            temp = temp->next;
        }
        return sum;
    }

};

void slide(int arr[], int size, int k){


    
}



int main(){




    return 0;
}