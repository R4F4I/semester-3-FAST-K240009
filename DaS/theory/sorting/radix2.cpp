/*



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
    // int size;

    Queue(int size = 0){
      head=nullptr;
      tail=nullptr;  
      this->size = size;
    }

    // current number of items in Queue
    // int  population(){
    //     Node* temp = head;
    //     int i = 1;
    //     while (temp!=tail)
    //     {
    //         temp = temp->next;
    //         i++;
    //     }
    //     return i;
    // }


    void Enq(int data){

        Node* newNode = new Node(data);


        if (head == nullptr){
            head = newNode;
            tail = newNode;
            return;
        }

        // if (population()>size)
        // {
            
        //     std::cout << "queue overflow!" << std::endl;
        //     // onw deq a val to enq
        //     Deq();
        // }
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


int NthDigit(int number, int k){


    // returns the nth digit of a number with k=0 being the most minimum,
    // any if k>number_digits -> returns 0

    int div = 1;
    for (size_t i = 0; i < k; i++)
    {
        div*=10;
    }
    number/=div; // now the target val is last digit

    return number%10;

};


bool isSorted(int arr[], int size){
    for (size_t i = 0; i < size-1; i++)
    {
        if (arr[i]>arr[i+1])
        {
            return false;
        }
        
    }
    return true;
    
}


/* 

first sort all the values with their first digit, by just placing them in a queue
then with theri 2nd digit, 3rd ,4th ...


*/
void radixSort(int arr[], int size){

    int i = 0;

    Queue bins[10];

    while (!isSorted(arr,size))
    {
        // put the vals in binss
        for (size_t j = 0; j < 10; j++)
        {
        
            if (NthDigit(arr[j],i)==j)
            {
                bins[i].Enq(arr[j]);
            }
        }
        // now dequeue all the values from all the bins, and into the array

        for (size_t i = 0; i < length; i++)
        {
            
        }

    }





}


int main(){

    cout << NthDigit(4567,1);

    int arr[] = {958,476,7896,3457,43857,48357,87439,4365,6755,9045};
    int size = 10;

    radixSort(arr,size);

    return 0;
}