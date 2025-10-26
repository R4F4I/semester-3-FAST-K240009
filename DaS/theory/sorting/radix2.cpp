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

    Queue(){
      head=nullptr;
      tail=nullptr;
    }



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

        if(tail!=nullptr){
            tail->next = nullptr;
        }else{
            head = nullptr;
        }

        delete temp;
        return val;
    }

    bool isEmpty(){
        return head==nullptr;
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

    void print() {
        Node* temp = head; // Start at the beginning
        
        while (temp != nullptr) 
        {
            std::cout << temp->data << " ";
            
            temp = temp->next;
        }
        
        std::cout << std::endl; 
    }

};



void printArr(int arr[], int size){

    
    for (size_t i = 0; i < size; i++)
    {
        std::cout << arr[i]<< " ";
    }
    cout<<endl;

}


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

    
    Queue bins[10];
    int n =0;
    while (!isSorted(arr,size))
    {
     
        
        // put the vals in bins
        for (size_t i = 0; i < size; i++)
        {
            // check arr[i]'s n th digit, put the arr[i]th val in the nth bin

            // bins[i].Enq(arr[i]);
            int keyDigit = NthDigit(arr[i],n);
            bins[keyDigit].Enq(arr[i]);


            
            
        }

        for (size_t i = 0; i < 10; i++)
        {
            // bins[i].print();
            /* code */
        }
        


        // now dequeue all the values from all the bins, and into the array
        
        int j = 0;
        for (size_t i = 0; i < 10; i++)
        {
            while (!bins[i].isEmpty())
            {
                arr[j] = bins[i].Deq();
                j++;
            }
            
        }
        
        n++;
        
    }
}


int main(){
    
    int arr[] = {959,478,7897,3456,4385,4834,8743,43652,67551,90450};
    int size = 10;
    
    radixSort(arr,size);
    
    printArr(arr,size);
    
    

    return 0;
}