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
    return nullptr;    
}

void linearInsert(int val, int table[],int size){
    for (size_t i = 0; i < size; i++){
        int target = (H(val,size)+i) % size; // move linearly in hashtable
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
        int target = (H(val,size)+i) % size;
        if (table[target]==val)
        {
            return target;
        }
        
    }
    return -1;    
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
    return -1;    
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
    cout << "=== HASH TABLE TESTING ===" << endl << endl;
    
    // ===== 1. SIMPLE HASH TABLE (No collision handling) =====
    cout << "1. SIMPLE HASH TABLE (No Collision Handling)" << endl;
    cout << "---------------------------------------------" << endl;
    int simpleTable[11];
    int size = 11;
    
    // Initialize
    for(int i = 0; i < size; i++) simpleTable[i] = -1;
    
    simpleInsert(23, simpleTable, size);
    simpleInsert(45, simpleTable, size);
    simpleInsert(67, simpleTable, size);
    
    cout << "Inserted: 23, 45, 67" << endl;
    cout << "Get 23: " << simpleGet(23, simpleTable, size) << endl;
    cout << "Get 45: " << simpleGet(45, simpleTable, size) << endl;
    
    // Show collision problem
    simpleInsert(34, simpleTable, size); // H(34) = 1, same as H(23)!
    cout << "Inserted 34 (collides with 23 at index 1)" << endl;
    cout << "Get 23: " << simpleGet(23, simpleTable, size) << " (OVERWRITTEN!)" << endl;
    cout << "Get 34: " << simpleGet(34, simpleTable, size) << endl;
    
    cout << "\nTable contents: ";
    for(int i = 0; i < size; i++){
        if(simpleTable[i] != -1) cout << "[" << i << "]=" << simpleTable[i] << " ";
    }
    cout << endl << endl;
    
    
    // ===== 2. CHAINING =====
    cout << "2. CHAINING (Linked Lists)" << endl;
    cout << "---------------------------------------------" << endl;
    Node* chainTable[11] = {nullptr};
    
    chainInsert(23, chainTable, size);
    chainInsert(45, chainTable, size);
    chainInsert(67, chainTable, size);
    chainInsert(34, chainTable, size); // Collides with 23
    chainInsert(12, chainTable, size); // Also at index 1
    
    cout << "Inserted: 23, 45, 67, 34, 12" << endl;
    cout << "Note: 23, 34, 12 all hash to index 1" << endl << endl;
    
    // Search for values
    Node* result = chainGet(34, chainTable, size);
    if(result) cout << "Found 34: " << result->data << endl;
    else cout << "34 not found" << endl;
    
    result = chainGet(99, chainTable, size);
    if(result) cout << "Found 99: " << result->data << endl;
    else cout << "99 not found" << endl;
    
    // Display chains
    cout << "\nChain contents:" << endl;
    for(int i = 0; i < size; i++){
        if(chainTable[i] != nullptr){
            cout << "Index " << i << ": ";
            Node* temp = chainTable[i];
            while(temp != nullptr){
                cout << temp->data << " -> ";
                temp = temp->next;
            }
            cout << "null" << endl;
        }
    }
    cout << endl;
    
    
    // ===== 3. LINEAR PROBING =====
    cout << "3. LINEAR PROBING" << endl;
    cout << "---------------------------------------------" << endl;
    int linearTable[11];
    for(int i = 0; i < size; i++) linearTable[i] = -1;
    
    linearInsert(23, linearTable, size);
    linearInsert(45, linearTable, size);
    linearInsert(67, linearTable, size);
    linearInsert(34, linearTable, size); // Collides at index 1
    linearInsert(12, linearTable, size); // Also collides
    
    cout << "Inserted: 23, 45, 67, 34, 12" << endl;
    cout << "H(23)=1, H(34)=1, H(12)=1 (collisions handled by probing)" << endl << endl;
    
    // Search
    int idx = linearSearch(34, linearTable, size);
    if(idx != -1) cout << "Found 34 at index: " << idx << endl;
    else cout << "34 not found" << endl;
    
    idx = linearSearch(12, linearTable, size);
    if(idx != -1) cout << "Found 12 at index: " << idx << endl;
    else cout << "12 not found" << endl;
    
    idx = linearSearch(99, linearTable, size);
    if(idx != -1) cout << "Found 99 at index: " << idx << endl;
    else cout << "99 not found" << endl;
    
    cout << "\nTable contents: ";
    for(int i = 0; i < size; i++){
        if(linearTable[i] != -1) cout << "[" << i << "]=" << linearTable[i] << " ";
    }
    cout << endl << endl;
    
    
    // ===== 4. QUADRATIC PROBING =====
    cout << "4. QUADRATIC PROBING" << endl;
    cout << "---------------------------------------------" << endl;
    int quadTable[11];
    for(int i = 0; i < size; i++) quadTable[i] = -1;
    
    quadraticInsert(23, quadTable, size);
    quadraticInsert(45, quadTable, size);
    quadraticInsert(67, quadTable, size);
    quadraticInsert(34, quadTable, size); // Collides, probes quadratically
    quadraticInsert(12, quadTable, size);
    
    cout << "Inserted: 23, 45, 67, 34, 12" << endl;
    cout << "Quadratic probing: (h + i²) mod size" << endl << endl;
    
    // Search
    idx = quadraticSearch(34, quadTable, size);
    if(idx != -1) cout << "Found 34 at index: " << idx << endl;
    else cout << "34 not found" << endl;
    
    idx = quadraticSearch(12, quadTable, size);
    if(idx != -1) cout << "Found 12 at index: " << idx << endl;
    else cout << "12 not found" << endl;
    
    idx = quadraticSearch(99, quadTable, size);
    if(idx != -1) cout << "Found 99 at index: " << idx << endl;
    else cout << "99 not found" << endl;
    
    cout << "\nTable contents: ";
    for(int i = 0; i < size; i++){
        if(quadTable[i] != -1) cout << "[" << i << "]=" << quadTable[i] << " ";
    }
    cout << endl << endl;
    
    
    // ===== 5. CLUSTERING DEMONSTRATION =====
    cout << "5. CLUSTERING COMPARISON" << endl;
    cout << "---------------------------------------------" << endl;
    
    int linearCluster[11];
    int quadCluster[11];
    for(int i = 0; i < size; i++){
        linearCluster[i] = -1;
        quadCluster[i] = -1;
    }
    
    // Insert values that all hash to index 1
    int values[] = {12, 23, 34, 45, 56, 67};
    
    cout << "Inserting values that all hash to index 1: ";
    for(int v : values) cout << v << " ";
    cout << endl << endl;
    
    for(int v : values){
        linearInsert(v, linearCluster, size);
        quadraticInsert(v, quadCluster, size);
    }
    
    cout << "Linear Probing (shows clustering): ";
    for(int i = 0; i < size; i++){
        if(linearCluster[i] != -1) cout << "[" << i << "]=" << linearCluster[i] << " ";
    }
    cout << endl;
    
    cout << "Quadratic Probing (less clustering): ";
    for(int i = 0; i < size; i++){
        if(quadCluster[i] != -1) cout << "[" << i << "]=" << quadCluster[i] << " ";
    }
    cout << endl << endl;
    
    
    // ===== 6. LOAD FACTOR DEMONSTRATION =====
    cout << "6. LOAD FACTOR IMPACT" << endl;
    cout << "---------------------------------------------" << endl;
    int smallTable[7];
    for(int i = 0; i < 7; i++) smallTable[i] = -1;
    
    cout << "Table size: 7" << endl;
    cout << "Inserting 5 elements (load factor = 5/7 = 0.71)" << endl;
    
    linearInsert(10, smallTable, 7);
    linearInsert(17, smallTable, 7);
    linearInsert(24, smallTable, 7);
    linearInsert(31, smallTable, 7);
    linearInsert(38, smallTable, 7);
    
    cout << "Table: ";
    for(int i = 0; i < 7; i++){
        if(smallTable[i] != -1) cout << "[" << i << "]=" << smallTable[i] << " ";
        else cout << "[" << i << "]=-  ";
    }
    cout << endl;
    cout << "Performance degrades as load factor approaches 1.0" << endl;
    cout << "Rehashing recommended when load factor > 0.7" << endl;
    
    
    // Cleanup chaining memory
    for(int i = 0; i < size; i++){
        Node* temp = chainTable[i];
        while(temp != nullptr){
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }
    
    return 0;
}