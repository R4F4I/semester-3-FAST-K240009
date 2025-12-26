/*

heap is a bst where the largest value is on top (max heap) or vice versa (min heap)


            10
           /  \
          15   30
         / \   / \
       40  50 100 40
        
         (min heap)

            10
           /  \
          15   30
         / \   / \
       100  50 40 40
            
        (min heap)
            
            
            100
           /   \ 
         40     50
        /  \   /  \
       10  15 50  40

        (max heap)

            44
           /  \ 
         42    35
        /  \   / \
      33   31 19 27
     / \   /
    10 26 14

        (max heap)



       */

#include <iostream>

using namespace std;

int parent(int i){
    return (i-1)/2; // truncate it to int
}

int left(int i){
    return (2*i)+1;
}

int right(int i){
    return (2*i)+2;
}


/* 

! HEAP IN ARRAYS

a heap is stored as an array, to keep  it balanced each is row is filled before a new row is defined

       0
   1       2
 3   4   5   6

to get heap[6] parent -> 6-1 = 5/2 = 2.5 = 2


*/



class heap
{

    // allocates 10 more space in the arr
    void allocateSpace(){
        int newSpace = space*2;
        int *newArr = new int[newSpace];
        
        for(int i = 0; i<newSpace; i++){
            newArr[i] = 0;
        }
        space =newSpace;

        for (size_t i = 0; i < space; i++){
            newArr[i] = this->arr[i];
        }
        delete[] arr; // remove all arr
        arr = newArr; // point to new arr
    }

    void append(int val){

        if (index>=space){
            allocateSpace();
        }
        

        this->arr[index] = val;
        index++;
    }

public:
    int *arr,index,space;
    
    heap(){
        index = 0;
        int *newArr = new int[10];
        space = 10;
        for (size_t i = 0; i < space; i++){
            newArr[i]=0;
        }
        
        arr = newArr;
    }


    /* 
    ! INSERTION:
    - value should be added from left first
        - if left is full then move it to right 
        - and if the entire entire row  is full then recursively move down
    - after every insertion a 'heapify' algorithm is performed to keep its property alive

    */


    void insert(int val){
        // first append this value
        // then perform heapifyUp
        append(val);
        heapifyUp();
        
    }


    
    /* 
    ! HEAPIFY

    - two variants, 'up' 'down'

    - heapifyUp
        - done during insertion
        - the child might be uneven node that needs to be sorted
        - it will move to the leaf node, and compare its parent
        - if the parent>child, swap them, until
        - root
        - parent<child

    - heapifyDown
        - done during deletion
        - the parent might be the uneven node that needs to be sorted

    */

    
    void heapifyUp(){
        // move to the left most node
        // it is the most recently added node
        // arr[size] is the left most node
        // compare it with its parent
        // if it is lesser than parent, swap
        
        int i = index-1; // marker for the latest added node
        while (arr[i]>arr[parent(i)] && i!=0 ){
            std::swap(arr[i],arr[parent(i)]);

            // after swapping update i to keep track of the node
            i = parent(i);
        }
        
    }

    void heapifyDown(){
        int i = 0;
        
        // Continue while node has at least a left child
        while (left(i) < index){
            int smallerChild = left(i);
            
            // Check if right child exists AND is smaller than left
            if (right(i) < index && arr[right(i)] < arr[smallerChild]){
                smallerChild = right(i);
            }
            
            // If parent is already smaller than smallest child, done
            if (arr[i] <= arr[smallerChild]){
                break;
            }
            
            // Swap with smaller child
            std::swap(arr[i], arr[smallerChild]);
            i = smallerChild;
        }
    }

    /* 
    ! DELETION
    * designed to ONLY return root
    - then place a leaf node as root then run 'heapifyDown'
        - choosing a node:
            - choose a node such that it balances the heap (right side first)
    */

    int remove(){
        // remove root, replace it with leaf node (last element)
        int root = arr[0];
        // last element
        arr[0] = arr[index-1];
        index--;

        heapifyDown();
        return root;
    }





    void printHeap() {
        for(int i=0; i<index; i++) std::cout << arr[i] << " ";
        std::cout << std::endl;
    }

    // returns a heapified array
    int* outArr(){
        return arr;
    }
};

void heapifyUp(int* arr, int index){
        
    int i = index-1; // marker for the latest added node
    while (arr[i]>arr[parent(i)] && i!=0 ){
        std::swap(arr[i],arr[parent(i)]);

        // after swapping update i to keep track of the node
        i = parent(i);
    }
    
}

void heapSort(int arr[], int size){

    while (size>1)
    {
        //1. create max heap
        heapifyUp(arr,size-1);
        //2. remove largest item
        size--;
        //3. place item in sorted partition
    }
}

int main(){

    int arr[] = {5,8,2,45,1,78,7,20,9,44,34,43,55,68,97,65,76,75,67,63,27,6,57,97,98,68,54,6};
    int size = sizeof(arr)/sizeof(arr[0]);
    std::cout << size << std::endl;

    heap h;
    for (size_t i = 0; i < size; i++)
    {
        h.insert(arr[i]);
    }

    int *newArr = h.outArr();
    

    heapSort(arr,size);

    // std::cout << isSorted(arr,size) << std::endl;
    // printArr(arr,size);
    


    return 0;
}