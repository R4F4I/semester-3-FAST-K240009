/*

suppose an arr, with val k, k is a window of size < arr.size

k will slide through the arr, and create a sum and place it in new,
this will create a new arr of same size that will have all the slided sums, find the largest val


* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;



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

class Queue {
    
public:
    Node *head, *tail;
    int size;

    Queue(int size = 0){
      head=nullptr;
      tail=nullptr;  
      this->size = size;
    }

    // current number of items in Queue
    int  population(){
        Node* temp = head;
        int i = 1;
        while (temp!=tail)
        {
            temp = temp->next;
            i++;
        }
        return i;
    }


    void Enq(int data){

        Node* newNode = new Node(data);


        if (head == nullptr){
            head = newNode;
            tail = newNode;
            return;
        }

        if (population()>size)
        {
            
            std::cout << "queue overflow!" << std::endl;
            // onw deq a val to enq
            Deq();
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

    void print(){
        Node* temp = head;
        while (temp!=tail)
        {
            std::cout << temp->data <<" ";
            temp = temp->next;
        }
        
    }

};

void slide(Queue q, int k){

    // plan:
    //  set the first pointer to point to the kth val in queue
    //  set the 2nd   pointer to point to the 1st val in queue
    // then sum all val b/w 1st node and kth node,
    // move the sum to an array,
    //      size of arr =  k - q.size
    // move increment first and 2nd pointer
    // repeat until kth pointer reaches tail



    
    
    // std::cout << "newArrSize: "<< newArrSize << std::endl;
    
    
    
    
    // NEW PLAN
    // CREATE A QUEUE OF SIZE K
    // ENQ ALL VAL IN Q, THEN SUM ITS VAL, THEN STORE IN SUM ARRAY
    
    Queue kQ(k);
    
    int newArrSize = q.size - k; // k is the size of the window, 
    
    int* arr = new int[newArrSize];
    
    for (size_t i = 0; i < newArrSize; i++)
    {
        // arr[i]=0;

        kQ.Enq(q.Deq());
        std::cout  << std::endl;
        std::cout << "kQ: " << std::endl;
        kQ.print();
        arr[i] = kQ.sum();
        std::cout << "kqsum: " <<kQ.sum()<< std::endl;
    }

    cout<<endl;
    for (size_t i = 0; i < newArrSize; i++)
    {
        std::cout << arr[i] <<" ";
    }
    
    
}



int main(){

    Queue queue(10);

    
    queue.Enq(9);
    queue.Enq(8);
    queue.Enq(7);

    queue.Enq(6);
    queue.Enq(5);
    queue.Enq(4);

    queue.Enq(3);
    queue.Enq(2);
    queue.Enq(1);
    // queue.Enq(10);

    // std::cout << queue.population() << std::endl;

    slide(queue,5);



    return 0;
}