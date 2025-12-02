/*

a hash(key) returns a arbitrary value, the value can be considered the key's address in a hash table
if the key is to be retrieved, then the hash will be used to get its addr -> O(1)

hence search, insert, remove -> O(1)

a hash() is bound to return duplicate values:
hash(key1) == hash(key2)
this causes collision in the hashtable

*/

#include <iostream>

using namespace std;

class Node
{
public:

    int data;
    Node *next;

    Node(int val=0){
        data = val;
        next = nullptr;
    }

};

class ll
{
public:
    Node *root;
    ll(){
        root = nullptr;
    }
    void insert(int val){
        Node *newNode = new Node(val);
        Node *temp = root;
        while (temp!=nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    Node* get(int val){
        Node *temp = root;
        while (temp!=nullptr)
        {
            if (temp->data == val)
            {
                return temp;
            }
            
            temp = temp->next;
        }
        
    }


};





/* 
! HASH EXAMPLE
- the simplest one is fitting all the values into a limited range
- this can be done using (mod tableSize)

*/

// best size is prime numbers, due to primes have the largest amount of remainders
int H(int n, int size){
    return n%size;
}



/* 

!RESOLVING COLLISION:

there are 2 ways

! CHAINING

- create a LL on the index where duplicates are present
- will waste space

! OPEN-ADDRESSING

- LINEAR PROBING
- will find the next nearest empty area in the hashtable
- has chances of values in table clustering

- QUADRATIC PROBING
- will find the next i*i empty area
- reduces clustering

- DOUBLE HASHING



*/

// creates a ll in the region where a duplicate was found

void chainInsert(int val, Node* table[], int size){
    // table is a list of pointers, each pointing to a root node of ll
    int target = H(val,size);

    Node* newNode = new Node(val);
    
    newNode->next = table[target];
    table[target] = newNode;

}

Node* chainGet(int val, Node* table[], int size){
    int index = H(val,size);

    Node *temp  = table[index];
    while (temp!=nullptr){
        if (temp->data==val)
            return temp;
        
        temp = temp->next;
        
    }
    
}

void linearInsert(int val, int table[],int size){
    for (size_t i = 0; i < size; i++){
        int target = H(val,size)+i % size; // move linearly in hashtable
        if (table[target]==-1){
            table[target] = val;
            break;
        }
        // linear probe creates clustering which means that keys are sorted in a continuous fashion, we can make the algo efficient by stopping if a continuous streak is broken 
        
    }
}

int linearSearch(int val, int table[], int size){
    // get starting point via hash
    for (size_t i = 0; i < size; i++)
    {
        int target = H(val,size)+i % size;
        if (table[target]==val)
        {
            return target;
        }
        
    }
    
}

void quadraticInsert(int val, int table[],int size){
    for (size_t i = 0; i < size; i++){
        int target = (H(val,size)+(i*i)) % size; // move quadratically in hashtable
        if (table[target]==-1){
            table[target] = val;
            break;
        }
    }
}

int quadraticSearch(int val, int table[], int size){
    // get starting point via hash
    for (size_t i = 0; i < size; i++)
    {
        int target = (H(val,size)+(i*i)) % size; // move quadratically in hashtable
        if (table[target]==val)
        {
            return target;
        }
        
    }
    
}


void simpleInsert(int val,int table[], int size){
    table[H(val,size)]=val;
}

int simpleGet(int val, int table[],int size){
    return table[H(val,size)];
}

/* 

! REHASHING
done when the number of elements relative to its size is too great
of load_factor>0.7~0.75

- aka when the table is too crowded

STEPS:
- new table (of size prime roughly double the current size)
- rehashing every item from old table when moving to new table
- replacing old table with new table
*/


int main(){


    Node* chainTable[61] = {};
    int size = 61;

    // simpleInsert(23,chainTable,65);

    chainInsert(23,chainTable,size);

    int simpletable[61] = {-1};
    int size = 61;


    return 0;
}