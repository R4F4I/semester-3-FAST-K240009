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
        while (arr[i]<arr[parent(i)] && i!=0 ){
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
};



int main() {
    heap h;
    
    h.insert(10);
    h.insert(15);
    h.insert(30);
    h.insert(40);
    h.insert(50);
    h.insert(100);
    
    // This one triggers the HeapifyUp!
    // It enters at end, but bubbles up to top because 5 is smallest.
    h.insert(5); 

    h.printHeap(); 
    // Expected Output: 5 15 10 40 50 100 30 (or similar valid heap structure)

    /* 
            5
          15 10
       40 50 100 30
    */
   std::cout << h.remove() << std::endl;
   h.printHeap();
   std::cout << h.remove() << std::endl;
   h.printHeap();
   std::cout << h.remove() << std::endl;
   h.printHeap();
   std::cout << h.remove() << std::endl;
   h.printHeap();

    return 0;
}